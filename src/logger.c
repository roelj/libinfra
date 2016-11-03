/*
 * Copyright © 2016  Roel Janssen <roel@gnu.org>
 *
 * This file is part of libinfra.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "libinfra/logger.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

struct infra_logger_t *
infra_logger_new (const char *filename)
{
  struct infra_logger_t *logger;
  logger = calloc (1, sizeof (struct infra_logger_t));

  if (logger == NULL)
    return NULL;

  logger->filename = strdup (filename);
  if (logger->filename == NULL)
    {
      free (logger);
      return NULL;
    }

  logger->file = fopen (logger->filename, "a");
  if (logger->file == NULL)
    {
      free (logger->filename);
      free (logger);
      return NULL;
    }

  return logger;
}

bool
infra_logger_log (struct infra_logger_t *logger,
                    enum log_priority_e priority,
                    const char *format, ...)
{
  if (logger == NULL || format == NULL)
    return false;

  if (logger->file == NULL)
    return false;

  char tag[13];
  memset (tag, 0, 13);

  switch (priority)
  {
    case LOG_ERROR_ALLOC:
    case LOG_ERROR:   strcpy (tag, "[ ERROR   ] "); break;
    case LOG_WARNING: strcpy (tag, "[ WARNING ] "); break;
    case LOG_INFO:    strcpy (tag, "[ INFO    ] "); break;
    case LOG_ACCESS:  strcpy (tag, "[ ACCESS  ] "); break;
    case LOG_TIMER:   strcpy (tag, "[ TIMER   ] "); break;
    default:          strcpy (tag, "[ UNKNOWN ] "); break;
  }

  va_list args;
  va_start (args, format);

  char message[LOG_MAX_MESSAGE_SIZE];
  memset (message, 0, LOG_MAX_MESSAGE_SIZE);

  time_t rawtime = time (NULL);
  char time_str[20];
  memset (time_str, 0, 20);

  strftime (time_str, 20, "%Y-%m-%d %H:%M:%S", localtime (&rawtime));

  if (vsnprintf (message, LOG_MAX_MESSAGE_SIZE, format, args) > 0
      && logger->file != NULL)
    {
      if (priority == LOG_ERROR_ALLOC)
        fprintf (logger->file, "%s %s :: Memory allocation error at %s.\n",
                 tag, time_str, message);
      else
        fprintf (logger->file, "%s %s :: %s\n", tag, time_str, message);

      fflush (logger->file);
    }
  else
    {
      va_end (args);
      return false;
    }

  va_end (args);
  return true;
}

bool
infra_logger_set_file (struct infra_logger_t *logger,
                             const char *filename)
{
  if (logger == NULL || filename == NULL)
    return false;

  if (logger->file != NULL)
    fclose (logger->file);

  if (logger->filename != NULL)
    free (logger->filename);

  logger->filename = strdup (filename);
  if (logger->filename == NULL)
    return false;

  logger->file = fopen (logger->filename, "a");
  return (logger->file != NULL);
}

void
infra_logger_destroy (struct infra_logger_t *logger)
{
  if (logger == NULL)
    return;

  free (logger->filename);
  fclose (logger->file);

  logger->filename = NULL;
  logger->file = NULL;

  free (logger);
}
