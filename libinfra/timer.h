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

#ifndef INFRA_TIMER_H
#define INFRA_TIMER_H

#include "logger.h"

#include <stdbool.h>
#include <time.h>

#define TIMER_MAX_NAME_LEN 255

/**
 * A timer that can measure how long an operation lasted.
 */
struct infra_timer_t
{
  char name[TIMER_MAX_NAME_LEN];
  clock_t start;
  clock_t stop;
};

/**
 * Constructor for a timer.
 * @param name  The name of the timer.
 *
 * @return A pointer to a dynamically allocated timer object.
 */
struct infra_timer_t * infra_timer_new (const char *name);

/**
 * Start a timer.
 * @param timer  The timer to start.
 */
void infra_timer_start (struct infra_timer_t *timer);

/**
 * Stop a timer.
 * @param timer  The timer to stop.
 */
void infra_timer_stop (struct infra_timer_t *timer);

/**
 * Write a timing to a server's log file.
 * @param logger  The logger object to use to log.
 * @param timer   The timer to log.
 *
 * @return true when a time was logged, false when nothing could be logged.
 */
bool
infra_timer_log (struct infra_logger_t *logger,
                 struct infra_timer_t *timer);

/**
 * Destructor for a timer object.
 * @param timer  The timer to destroy.
 */
void infra_timer_destroy (struct infra_timer_t *timer);

#endif
