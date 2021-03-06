/*
 *
 * Copyright (c) 2014-2020 Embedded Systems and Applications, TU Darmstadt.
 *
 * This file is part of TaPaSCo
 * (see https://github.com/esa-tu-darmstadt/tapasco).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */
/**
  * @file LogFormatter.scala
  * @brief Formats TPC objects for log output.
  * @authors J. Korinth, TU Darmstadt (jk@esa.cs.tu-darmstadt.de)
  **/
package tapasco.util

import tapasco.activity.composers._
import tapasco.base.Composition
import tapasco.dse.DesignSpace

object LogFormatter {
  def logformat(ce: Composition.Entry): String =
    "%s x %d".format(ce.kernel, ce.count)

  def logformat(c: Composition): String =
    "%s[%s]".format(c.id, c.composition.map(logformat) mkString ", ")

  def logformat(de: DesignSpace.Element): String =
    "%s[F=%3.3f] with (h = %3.5f)".format(logformat(de.composition), de.frequency, de.h)

  def logformat(ce: Composer.Result): String =
    "%s, logfile: '%s', utilization report: '%s', timing report: '%s'"
      .format(ce.result,
        ce.log map (_.file.toString) getOrElse "",
        ce.util map (_.file.toString) getOrElse "",
        ce.timing map (_.file.toString) getOrElse "")

  def logformat(cs: Seq[Composition.Entry]): String = "[%s]".format(cs map (logformat _) mkString ", ")
}
