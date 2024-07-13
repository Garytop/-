#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

int indexOf(const char * original, const char * target);

char *substr(const char * original, int a, int length);

int parse_valgrind(const char *str, const char *pre, const char *mid, const char *post);

int test1();

int test2();

int test3();

int test4();

int test5();

int test6();

int test7();

int test8();

int test9();

int usage();

int fame();

int print_time();

int print_time() {
    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", tm_info);
    puts(buffer);

    return 0;
}

/*
 Tested at 2013-01-30 14:07:27

 Testing Status
 ================================================
 InvertColorsEven  . . [33 point(s)] - passed
 FlipLeftEven  . . . . [17 point(s)] - passed
 FlipLeftOdd . . . . . [17 point(s)] - passed
 AdjustBrightnessEven  [11 point(s)] - passed
 AdjustBrightnessEven2 [11 point(s)] - passed
 AdjustBrightnessEven3 [11 point(s)] - passed

 Total Score
 ================================================
 100
 */

int main() {
    int pts = 0;
    printf("[");
    int pt1 = test1();
    pts += (pt1*10);
    if (pt1) {
        pts += (test2()*20);
        pts += (test3()*20);
    } else {
        printf("{\"name\":\"Time Attack 1\",\"totalScore\":20,\"passed\":false},");
        printf("{\"name\":\"Memory Test 1\",\"totalScore\":20,\"passed\":false},");
    }
    int pt2 = test4();
    if (pt2) {
        pts += (test5()*20);
        pts += (test6()*20);
    } else {
        printf("{\"name\":\"Time Attack 2\",\"totalScore\":20,\"passed\":false},");
        printf("{\"name\":\"Memory Test 2\",\"totalScore\":20,\"passed\":false}");
    }
    printf("]");
    // int pt3 = test7();
    // if (pt3) {
    //     pts += (test8()*20);
    // } else {
    //     printf("{\"name\":\"Time Attack 3\",\"totalScore\":10,\"passed\":false}]");
    // }
    return 0;
}

int usage() {
    printf("Usage: ./test\n");
    exit(1);
}

int test1() {
  pid_t p1 = fork();
  if (p1 == 0) {          //child process
      int fd = open("output/part1.txt", O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
      if (fd < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      dup2(fd, STDOUT_FILENO);
      execlp("./part1", "./part1", NULL);
      perror("Execlp Failed: ");    //this line is not supposed to be executed
      exit(1);                      //this line is not supposed to be executed
  } else if (p1 > 0) {       //parent process
      int status;
      pid_t w_result = waitpid(p1, &status, 0);

      if (w_result == -1) {
          perror("Failed to wait");
          exit(1);
      }

      pid_t p2 = fork();
      if (p2 == 0) {
          int fd_null = open("/dev/null", O_RDWR);
          dup2(fd_null, STDOUT_FILENO);
          execlp("diff", "diff", "output/part1.txt", "output/part1_sol.txt", NULL);
          perror("Execlp diff Failed: ");    //this line is not supposed to be executed
          exit(1);
      } else if (p2 > 0) {
          int status2;
          waitpid(p2, &status2, 0);
          if (WIFEXITED(status2)) {
              if (WEXITSTATUS(status2) != 0) {
                  printf("{\"name\":\"Basic Test 1\",\"totalScore\":10,\"passed\":false},");
                  return 0;
              } else {
                  printf("{\"name\":\"Basic Test 1\",\"totalScore\":10,\"passed\":true},");
                  return 1;
              }
          }
      } else {
          perror("Failed to fork");
          exit(1);
      }
  } else {
      perror("Failed to fork");
      exit(1);
  }
  return 0;
}

int test2() {
  pid_t p = fork();
  if (p == 0) {
      int fd = open("output/part2.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
      dup2(fd, STDERR_FILENO);
      close(fd);

      int fd_null = open("/dev/null", O_RDWR);
      if (fd_null < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      dup2(fd_null, STDOUT_FILENO);

      system("time ./part1");

      perror("Execlp Failed: ");    //this line is not supposed to be executed
      exit(1);                      //this line is not supposed to be executed
  } else if (p > 0) {
      int status;
      pid_t w_result = waitpid(p, &status, 0);
      if (w_result == -1) {
          perror("Wait Failed: ");
          exit(1);
      }

      FILE *fp = fopen("output/part2.txt", "r");
      char *buffer = NULL;
      size_t n = 0;
      //int min;
      float sec = -1, m = 0;
      getline(&buffer, &n, fp);
      if (getline(&buffer, &n, fp) != -1) {
          sscanf(buffer, "real    %fm%f", &m, &sec);
          free(buffer);
          buffer = NULL;

          free(buffer);
          buffer = NULL;
      }
      free(buffer);
      fclose(fp);
      //printf("Hash result 2: %ld\n", xor_hash_2);
      if (sec < 2 && sec != -1) {
          printf("{\"name\":\"Time Attack 1\",\"totalScore\":20,\"passed\":true},");
          return 1;
      } else {
          printf("{\"name\":\"Time Attack 1\",\"totalScore\":20,\"passed\":false},");
          return 0;
      }
  } else {
      perror("Fork Failed: ");
      exit(1);
  }
  return 0;
}

int test3(){
  pid_t p1 = fork();
  if (p1 == 0) {          //child process
      int fd = open("output/part3.txt", O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
      if (fd < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      int fd_null = open("/dev/null", O_RDWR);
      if (fd_null < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      dup2(fd_null, STDOUT_FILENO);
      dup2(fd, STDERR_FILENO);
      execlp("valgrind", "valgrind", "./part1", NULL);
      perror("Execlp Failed: ");    //this line is not supposed to be executed
      exit(1);                      //this line is not supposed to be executed
  } else if (p1 > 0) {       //parent process
      int status;
      pid_t w_result = waitpid(p1, &status, 0);

      if (w_result == -1) {
          perror("Failed to wait");
          exit(1);
      }
      const char *file_name = "output/part3.txt";

      FILE *fp = fopen(file_name, "r");

      fseek(fp, 0, SEEK_END);
      int length = ftell(fp);
      fseek(fp, 0, SEEK_SET);
      char *buffer = (char *)calloc((length+1) * sizeof(char), 1);
      fread(buffer, sizeof(char), length, fp);

      int ret = parse_valgrind(buffer, "in use at exit: ", " bytes in ", " blocks\n==");
      ret += parse_valgrind(buffer, "== ERROR SUMMARY: ", " errors from ", " contexts ");
      if (ret == 0) {
          printf("{\"name\":\"Memory Test 1\",\"totalScore\":20,\"passed\":true},");
          return 1;
      } else {
          printf("{\"name\":\"Memory Test 1\",\"totalScore\":20,\"passed\":false},");
          return 0;
      }

  } else {
      perror("Failed to fork");
      exit(1);
  }
  return 0;
}

int test4() {
  pid_t p1 = fork();
  if (p1 == 0) {          //child process
      int fd = open("output/part4.txt", O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
      if (fd < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      dup2(fd, STDOUT_FILENO);
      execlp("./part2", "./part2", NULL);
      perror("Execlp Failed: ");    //this line is not supposed to be executed
      exit(1);                      //this line is not supposed to be executed
  } else if (p1 > 0) {       //parent process
      int status;
      pid_t w_result = waitpid(p1, &status, 0);

      if (w_result == -1) {
          perror("Failed to wait");
          exit(1);
      }

      pid_t p2 = fork();
      if (p2 == 0) {
          int fd_null = open("/dev/null", O_RDWR);
          dup2(fd_null, STDOUT_FILENO);
          execlp("diff", "diff", "output/part4.txt", "output/part2_sol.txt", NULL);
          perror("Execlp diff Failed: ");    //this line is not supposed to be executed
          exit(1);
      } else if (p2 > 0) {
          int status2;
          waitpid(p2, &status2, 0);
          if (WIFEXITED(status2)) {
              if (WEXITSTATUS(status2) != 0) {
                  printf("{\"name\":\"Basic Test 2\",\"totalScore\":10,\"passed\":false},");
                  return 0;
              } else {
                  printf("{\"name\":\"Basic Test 2\",\"totalScore\":10,\"passed\":true},");
                  return 1;
              }
          }
      } else {
          perror("Failed to fork");
          exit(1);
      }
  } else {
      perror("Failed to fork");
      exit(1);
  }
  return 0;
}

int test5() {
  pid_t p = fork();
  if (p == 0) {
      int fd = open("output/part5.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
      dup2(fd, STDERR_FILENO);
      close(fd);

      int fd_null = open("/dev/null", O_RDWR);
      if (fd_null < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      dup2(fd_null, STDOUT_FILENO);

      system("time ./part2");

      perror("Execlp Failed: ");    //this line is not supposed to be executed
      exit(1);                      //this line is not supposed to be executed
  } else if (p > 0) {
      int status;
      pid_t w_result = waitpid(p, &status, 0);
      if (w_result == -1) {
          perror("Wait Failed: ");
          exit(1);
      }

      FILE *fp = fopen("output/part5.txt", "r");
      char *buffer = NULL;
      size_t n = 0;
      //int min;
      float sec = -1, m = 0;
      getline(&buffer, &n, fp);
      if (getline(&buffer, &n, fp) != -1) {
          sscanf(buffer, "real    %fm%f", &m, &sec);
          free(buffer);
          buffer = NULL;

          free(buffer);
          buffer = NULL;
      }
      free(buffer);
      fclose(fp);
      //printf("Hash result 2: %ld\n", xor_hash_2);
      if (sec < 8 && sec != -1) {
          printf("{\"name\":\"Time Attack 2\",\"totalScore\":20,\"passed\":true},");
          return 1;
      } else {
          printf("{\"name\":\"Time Attack 2\",\"totalScore\":20,\"passed\":false},");
          return 0;
      }
  } else {
      perror("Fork Failed: ");
      exit(1);
  }
  return 0;
}

int test6(){
  pid_t p1 = fork();
  if (p1 == 0) {          //child process
      int fd = open("output/part6.txt", O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
      if (fd < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      int fd_null = open("/dev/null", O_RDWR);
      if (fd_null < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      dup2(fd_null, STDOUT_FILENO);
      dup2(fd, STDERR_FILENO);
      execlp("valgrind", "valgrind", "./part2", NULL);
      perror("Execlp Failed: ");    //this line is not supposed to be executed
      exit(1);                      //this line is not supposed to be executed
  } else if (p1 > 0) {       //parent process
      int status;
      pid_t w_result = waitpid(p1, &status, 0);

      if (w_result == -1) {
          perror("Failed to wait");
          exit(1);
      }
      const char *file_name = "output/part6.txt";

      FILE *fp = fopen(file_name, "r");

      fseek(fp, 0, SEEK_END);
      int length = ftell(fp);
      fseek(fp, 0, SEEK_SET);
      char *buffer = (char *)calloc((length+1) * sizeof(char), 1);
      fread(buffer, sizeof(char), length, fp);

      int ret = parse_valgrind(buffer, "in use at exit: ", " bytes in ", " blocks\n==");
      ret += parse_valgrind(buffer, "== ERROR SUMMARY: ", " errors from ", " contexts ");
      if (ret == 0) {
          printf("{\"name\":\"Memory Test 2\",\"totalScore\":20,\"passed\":true}");
          return 1;
      } else {
          printf("{\"name\":\"Memory Test 2\",\"totalScore\":20,\"passed\":false}");
          return 0;
      }

  } else {
      perror("Failed to fork");
      exit(1);
  }
  return 0;
}

int test7() {
  pid_t p1 = fork();
  if (p1 == 0) {          //child process
      int fd = open("output/part7.txt", O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
      if (fd < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      dup2(fd, STDOUT_FILENO);
      execlp("./part3", "./part3", NULL);
      perror("Execlp Failed: ");    //this line is not supposed to be executed
      exit(1);                      //this line is not supposed to be executed
  } else if (p1 > 0) {       //parent process
      int status;
      pid_t w_result = waitpid(p1, &status, 0);

      if (w_result == -1) {
          perror("Failed to wait");
          exit(1);
      }

      pid_t p2 = fork();
      if (p2 == 0) {
          int fd_null = open("/dev/null", O_RDWR);
          dup2(fd_null, STDOUT_FILENO);
          execlp("diff", "diff", "output/part7.txt", "output/part3_sol.txt", NULL);
          perror("Execlp diff Failed: ");    //this line is not supposed to be executed
          exit(1);
      } else if (p2 > 0) {
          int status2;
          waitpid(p2, &status2, 0);
          if (WIFEXITED(status2)) {
              if (WEXITSTATUS(status2) != 0) {
                  printf("{\"name\":\"Basic Test 3\",\"totalScore\":20,\"passed\":false},");
                  return 0;
              } else {
                  printf("{\"name\":\"Basic Test 3\",\"totalScore\":20,\"passed\":true},");
                  return 1;
              }
          }
      } else {
          perror("Failed to fork");
          exit(1);
      }
  } else {
      perror("Failed to fork");
      exit(1);
  }
  return 0;
}

int test8() {
  pid_t p = fork();
  if (p == 0) {
      int fd = open("output/part8.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
      dup2(fd, STDERR_FILENO);
      close(fd);

      int fd_null = open("/dev/null", O_RDWR);
      if (fd_null < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      dup2(fd_null, STDOUT_FILENO);

      system("time ./part3");

      perror("Execlp Failed: ");    //this line is not supposed to be executed
      exit(1);                      //this line is not supposed to be executed
  } else if (p > 0) {
      int status;
      pid_t w_result = waitpid(p, &status, 0);
      if (w_result == -1) {
          perror("Wait Failed: ");
          exit(1);
      }

      FILE *fp = fopen("output/part8.txt", "r");
      char *buffer = NULL;
      size_t n = 0;
      //int min;
      float sec = -1, m = 0;
      getline(&buffer, &n, fp);
      if (getline(&buffer, &n, fp) != -1) {
          sscanf(buffer, "real    %fm%f", &m, &sec);
          free(buffer);
          buffer = NULL;

          free(buffer);
          buffer = NULL;
      }
      free(buffer);
      fclose(fp);
      //printf("Hash result 2: %ld\n", xor_hash_2);
      if (sec < 12 && sec != -1) {
          printf("{\"name\":\"Time Attack 3\",\"totalScore\":20,\"passed\":true}]");
          return 1;
      } else {
          printf("{\"name\":\"Time Attack 3\",\"totalScore\":20,\"passed\":false}]");
          return 0;
      }
  } else {
      perror("Fork Failed: ");
      exit(1);
  }
  return 0;
}

int test9(){
  pid_t p1 = fork();
  if (p1 == 0) {          //child process
      int fd = open("output/part9.txt", O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
      if (fd < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      int fd_null = open("/dev/null", O_RDWR);
      if (fd_null < 0) {
          perror("Failed to open txt file ");
          exit(1);
      }
      dup2(fd_null, STDOUT_FILENO);
      dup2(fd, STDERR_FILENO);
      execlp("valgrind", "valgrind", "./part3", NULL);
      perror("Execlp Failed: ");    //this line is not supposed to be executed
      exit(1);                      //this line is not supposed to be executed
  } else if (p1 > 0) {       //parent process
      int status;
      pid_t w_result = waitpid(p1, &status, 0);

      if (w_result == -1) {
          perror("Failed to wait");
          exit(1);
      }
      const char *file_name = "output/part9.txt";

      FILE *fp = fopen(file_name, "r");

      fseek(fp, 0, SEEK_END);
      int length = ftell(fp);
      fseek(fp, 0, SEEK_SET);
      char *buffer = (char *)calloc((length+1) * sizeof(char), 1);
      fread(buffer, sizeof(char), length, fp);

      int ret = parse_valgrind(buffer, "in use at exit: ", " bytes in ", " blocks\n==");
      ret += parse_valgrind(buffer, "== ERROR SUMMARY: ", " errors from ", " contexts ");
      if (ret == 0) {
          printf("{\"name\":\"Memory Test 3\",\"totalScore\":10,\"passed\":true}]");
          return 1;
      } else {
          printf("{\"name\":\"Memory Test 3\",\"totalScore\":10,\"passed\":false}]");
          return 0;
      }

  } else {
      perror("Failed to fork");
      exit(1);
  }
  return 0;
}

int parse_valgrind(const char *str, const char *pre, const char *mid, const char *post) {
    int start = indexOf(str, pre);
    int end = indexOf(str, post);
    char *potential_line = substr(str, start, end - start + strlen(post));
    start = indexOf(potential_line, pre);
    int length = strlen(pre);
    end = indexOf(potential_line, mid);
    char *tmp1 = substr(potential_line, start + length, end - (start + length));
    int num_bytes = atoi(tmp1);
    free(tmp1);
    start = end;
    end = indexOf(potential_line, post);
    length = strlen(mid);

    char * tmp2 = substr(potential_line, start + length, end - (start + length) );
    int num_blocks = atoi(tmp2);
    free(tmp2);

    free(potential_line);
    //printf("a: %d, b: %d\n", num_bytes, num_blocks);
    if (num_bytes == 0 && num_blocks == 0) {
        return 0;
    }
    return 1;
}

/*
 Example: Original: "Lisongyu is handsome."
 Target:   "songyu"
 return == 2
 */
int indexOf(const char * original, const char * target) {
    //int it = 0;
    int length_original = strlen(original);
    int length_target = strlen(target);
    for (int i = 0; i < length_original; i++ ) {
        if (length_original - i - 1 < length_target) {
            break;
        }
        int j = i;
        int n = 0;
        while (original[j] == target[n] && n < length_target) {
            j++;
            n++;
        }
        if (n == length_target) {
            return i;
        }
    }
    return -1;
}

char *substr(const char * original, int a, int length) {
    if (a >= (int)strlen(original)) {
        return NULL;
    }
    if (a + length >= (int)strlen(original)) {
        return strdup( (char *) (original + a));
    }
    char *tmp = strdup(original);
    tmp[a+length] = '\0';
    char *ret = strdup(tmp + a);
    free(tmp);
    return ret;
}

int fame() {
    srand(time(NULL));
    rand();
    int r = rand();
    if (r % 6 == 0) {
        printf("\"计算机科学并不只关于计算机，就像天文学不研究望远镜一样。\" ——（讹）艾兹赫尔·戴克斯特拉\n");
        printf("\"Computer Science is no more about computers than astronomy is about telescopes.\" — (Mis)attributed to Edsger Dijkstra, 1970.\n");
    } else if (r % 6 == 1) {
        printf("\"计算机科学领域的任何问题都可以通过增加一个间接的中间层来解决。\"\n");
        printf("\"Any problem in computer science can be solved with another level of indirection.\"\n");
    } else if (r % 6 == 2) {
        printf("\"计算机科学既不是数学也不是电子工程学。\" —— 艾伦·佩利\n");
        printf("\"Computer science is neither mathematics nor electrical engineering.\" - Alan Perlis\n");
    } else if (r % 6 == 3) {
        printf("\"计算机科学是一门经验科学。\" —— 艾伦·纽厄尔\n");
        printf("\"Computer science is an empirical discipline.\" - Allen Newell\n");
    } else if (r % 6 == 4) {
        printf("\"计算机没什么用，他们只会告诉你答案。\" —— 巴勃罗·毕加索\n");
        printf("\"Computers are useless. They can only give you answers.\" - Pablo Picasso\n");
    } else {
        printf("\"计算机科学与物理学的不同点就是... 它根本不是一门科学。\" —— 理查德·费曼\n");
        printf("\"Computer science... differs from physics in that it is not actually a science.\" - Richard Feynman\n");
    }
    return 0;
}
