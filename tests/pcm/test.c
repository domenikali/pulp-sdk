/**
 * Test suite for PCM (Phase change memory) module.
 * @author: Leonardo Domenicali (leonardo.domenicali@studio.unibo.it | leonardo.domenicali@gmail.com)
 */
#include "pmsis.h"

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

typedef enum {
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR
} LogLevel;

void log(LogLevel level, const char *format, ...){
  va_list args;
  va_start(args, format);
  switch(level){
    case LOG_INFO:
      printf(ANSI_COLOR_BLUE "INFO: ");
      break;
    case LOG_WARNING:
      printf(ANSI_COLOR_YELLOW "WARNING: " );
      break;
    case LOG_ERROR:
      printf(ANSI_COLOR_RED "ERROR: ");
      break;
    default:
      printf("UNKNOWN: ");
      break;
  }

  vprintf(format, args);
  printf(ANSI_COLOR_RESET "\n");
  va_end(args);
}

static int test_entry()
{
  log(LOG_INFO,"info");
  log(LOG_WARNING,"warning");
  log(LOG_ERROR,"error");
  return 0;
}

static void test_kickoff(void *arg)
{
  int ret = test_entry();
    
  pmsis_exit(ret);

}

int main()
{
  return pmsis_kickoff((void *)test_kickoff);
}