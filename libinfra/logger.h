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

#ifndef INFRA_LOGGER_H
#define INFRA_LOGGER_H

#define LOG_MAX_MESSAGE_SIZE 1024

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * An enumeration of priorities that can be assigned to log messages.
 */
enum log_priority_e {
  LOG_ERROR_ALLOC,
  LOG_ERROR,
  LOG_WARNING,
  LOG_INFO,
  LOG_TIMER,
  LOG_ACCESS
}; 

/**
 * A logger object.
 */
struct infra_logger_t
{
  char *filename;
  FILE *file;
};

/**
 * Constructor for a logger object.
 * @return A pointer to a dynamically allocated infra_logger_t object.
 */
struct infra_logger_t * infra_logger_new (const char *filename);

/**
 * Writes a log message to the server's log file.  Messages can contain any
 * number of arguments, and the format can be given in just the same way as
 * printf.
 * @param server    The server to write a log message for.
 * @param priority  The priority of the log message.
 * @param format    The format specifier for the message.
 *
 * @return true on success, false on failure.
 */
bool infra_logger_log (struct infra_logger_t *logger,
                       enum log_priority_e priority,
                       const char *message, ...);

#define infra_logger_error_alloc(logger) infra_logger_log (logger,            \
                                                           LOG_ERROR_ALLOC,   \
                                                           "%s:%d (%s)",      \
                                                           __FILE__,          \
                                                           __LINE__, __func__);
 

/**
 * Destructor for a logger object.
 * @param logger  The logger object to destroy.
 */
void infra_logger_destroy (struct infra_logger_t *logger);

#endif
