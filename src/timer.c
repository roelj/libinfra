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

#include "libinfra/timer.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct infra_timer_t *
infra_timer_new (const char *name)
{
  struct infra_timer_t *timer;
  timer = calloc (1, sizeof (struct infra_timer_t));
  if (timer == NULL)
    return NULL;

  strncpy (timer->name, name, TIMER_MAX_NAME_LEN - 1);
  timer->name[TIMER_MAX_NAME_LEN - 1] = '\0';

  return timer;
}

void
infra_timer_start (struct infra_timer_t *timer)
{
  if (timer == NULL)
    return;

  timer->start = clock ();
}

void
infra_timer_stop (struct infra_timer_t *timer)
{
  timer->stop = clock ();
}

bool
infra_timer_log (struct infra_logger_t *logger,
                 struct infra_timer_t *timer)
{
  if (logger == NULL || timer == NULL)
    return false;

  if (timer->start == 0 || timer->stop == 0)
    return false;

  double time_spent = (double)(timer->stop - timer->start) / CLOCKS_PER_SEC;
  infra_logger_log (logger, LOG_TIMER, "%s took %f seconds",
                    timer->name, time_spent);

  return true;
}

void
infra_timer_destroy (struct infra_timer_t *timer)
{
  free (timer);
}
