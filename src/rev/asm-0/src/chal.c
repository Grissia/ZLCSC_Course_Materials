#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

// gcc chal.c -o chal -std=c17

#define MAX_ASM_SIZE 8192

static void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

static void banner() {
    puts("=====================================");
    puts("Welcome to the asm-0 Challenge!");
    puts("Submit x86_64 Intel syntax assembly.");
    puts("End input with a line containing only: END");
    puts("Goal: open/read/write /flag.txt");
    puts("=====================================");
}

static size_t read_asm(char *buf, size_t max) {
    size_t used = 0;
    char line[512];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        size_t line_len = strlen(line);
        while (line_len > 0) {
            char c = line[line_len - 1];
            if (c == '\n' || c == '\r' || c == ' ' || c == '\t') {
                line[--line_len] = '\0';
                continue;
            }
            break;
        }
        if (strcmp(line, "END") == 0) {
            break;
        }
        size_t len = line_len;
        if (used + len >= max) {
            fprintf(stderr, "[error] assembly too large\n");
            return 0;
        }
        if (len == 0) {
            continue;
        }
        memcpy(buf + used, line, len);
        used += len;
        buf[used++] = '\n';
    }
    return used;
}

static int write_file(const char *path, const char *data, size_t len) {
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    ssize_t wrote = write(fd, data, len);
    if (wrote < 0 || (size_t)wrote != len) {
        perror("write");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

static int read_file(const char *path, unsigned char **out, size_t *out_len) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    off_t size = lseek(fd, 0, SEEK_END);
    if (size <= 0) {
        perror("lseek");
        close(fd);
        return -1;
    }
    if (lseek(fd, 0, SEEK_SET) < 0) {
        perror("lseek");
        close(fd);
        return -1;
    }
    unsigned char *buf = malloc((size_t)size);
    if (!buf) {
        perror("malloc");
        close(fd);
        return -1;
    }
    ssize_t got = read(fd, buf, (size_t)size);
    if (got < 0 || got != size) {
        perror("read");
        free(buf);
        close(fd);
        return -1;
    }
    close(fd);
    *out = buf;
    *out_len = (size_t)size;
    return 0;
}

int main() {
    init();
    banner();

    puts("Hint: syscalls use rax, rdi, rsi, rdx.");

    char asm_buf[MAX_ASM_SIZE];
    size_t asm_len = read_asm(asm_buf, sizeof(asm_buf));
    if (asm_len == 0) {
        fprintf(stderr, "[error] no input\n");
        return 1;
    }

    char asm_path[] = "/tmp/asm-XXXXXX";
    char bin_path[] = "/tmp/bin-XXXXXX";
    int asm_fd = mkstemp(asm_path);
    if (asm_fd < 0) {
        perror("mkstemp");
        return 1;
    }
    close(asm_fd);
    int bin_fd = mkstemp(bin_path);
    if (bin_fd < 0) {
        perror("mkstemp");
        unlink(asm_path);
        return 1;
    }
    close(bin_fd);

    const char *prefix = "BITS 64\nGLOBAL asm_entry\n";
    const char *label = "asm_entry:\n";
    size_t total = strlen(prefix) + strlen(label) + asm_len + 1;
    char *full = malloc(total);
    if (!full) {
        perror("malloc");
        return 1;
    }
    size_t offset = 0;
    memcpy(full + offset, prefix, strlen(prefix));
    offset += strlen(prefix);
    memcpy(full + offset, label, strlen(label));
    offset += strlen(label);
    memcpy(full + offset, asm_buf, asm_len);
    offset += asm_len;
    full[offset] = '\0';

    if (write_file(asm_path, full, offset) != 0) {
        free(full);
        unlink(asm_path);
        unlink(bin_path);
        return 1;
    }
    free(full);

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "nasm -f bin %s -o %s", asm_path, bin_path);
    puts("Assembling...");
    int rc = system(cmd);
    if (rc != 0) {
        fprintf(stderr, "[error] nasm failed\n");
        unlink(asm_path);
        unlink(bin_path);
        return 1;
    }

    unsigned char *code = NULL;
    size_t code_len = 0;
    if (read_file(bin_path, &code, &code_len) != 0) {
        unlink(asm_path);
        unlink(bin_path);
        return 1;
    }

    printf("Assembled %zu bytes\n", code_len);
    void *mem = mmap(NULL, code_len, PROT_READ | PROT_WRITE | PROT_EXEC,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        perror("mmap");
        free(code);
        return 1;
    }
    memcpy(mem, code, code_len);
    free(code);
    unlink(asm_path);
    unlink(bin_path);

    printf("Entry at %p\n", mem);
    int (*entry)() = (int (*)())mem;
    int ret = entry();
    printf("Returned %d\n", ret);
    puts("Execution complete.");

    munmap(mem, code_len);
    return 0;
}
