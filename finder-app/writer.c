#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    openlog("writer", 0, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments: expected 2, got %d", argc - 1);
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];
    size_t len = strlen(writestr);

    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Could not open %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: could not open %s: %s\n", writefile, strerror(errno));
        closelog();
        return 1;
    }

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    size_t done = 0;
    while (done < len) {
        ssize_t n = write(fd, writestr + done, len - done);
        if (n == -1) {
            if (errno == EINTR)
                continue;
            syslog(LOG_ERR, "Could not write to %s: %s", writefile, strerror(errno));
            fprintf(stderr, "Error: could not write to %s: %s\n", writefile, strerror(errno));
            close(fd);
            closelog();
            return 1;
        }
        done += n;
    }

    if (close(fd) == -1) {
        syslog(LOG_ERR, "Could not close %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: could not close %s: %s\n", writefile, strerror(errno));
        closelog();
        return 1;
    }

    closelog();
    return 0;
}
