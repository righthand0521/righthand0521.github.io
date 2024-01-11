#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <shadow.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <crypt.h>


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <user name>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *pName = argv[1];

    int ret = system("uname -a");
    if (WIFSIGNALED(ret) && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT))
    {
        perror("system");
        return EXIT_FAILURE;
    }

    // get password file entry: http://man7.org/linux/man-pages/man3/getpwnam.3.html
    struct passwd *user = getpwnam(pName);
    printf("username:           [%s]\n", user->pw_name);
    printf("user password:      [%s]\n", user->pw_passwd);
    printf("user ID:            [%d]\n", user->pw_uid);
    printf("group ID:           [%d]\n", user->pw_gid);
    printf("user information:   [%s]\n", user->pw_gecos);
    printf("home directory:     [%s]\n", user->pw_dir);
    printf("shell program:      [%s]\n", user->pw_shell);

    // get shadow password file entry: http://man7.org/linux/man-pages/man3/getspnam.3.html
    struct spwd *spasswd = getspnam(user->pw_name);
    printf("Login name:         [%s]\n", spasswd->sp_namp);
    printf("Encrypted password: [%s]\n", spasswd->sp_pwdp);
    printf("crypt(12345678):    [%s]\n", crypt("12345678", spasswd->sp_pwdp));
    printf("crypt(abcdefg):     [%s]\n", crypt("abcdefg", spasswd->sp_pwdp));

    char *passwdcrypt = "$1$o/...h/.$MNgdjHrFe1yu4v5pLIDbR1";
    printf("passwdcrypt:        [%s]\n", passwdcrypt);
    printf("crypt(password):    [%s]\n", crypt("password", passwdcrypt));
    printf("crypt(12345678):    [%s]\n", crypt("12345678", passwdcrypt));


    return EXIT_SUCCESS;
}

