/* -*- c++ -*- */
/*
 * Copyright 2019 Lime Microsystems.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "source_impl.h"

namespace gr {
  namespace limesdr {

    source::sptr
    source::make(std::string serial, int channel_mode, const std::string& filename)
    {
      return gnuradio::get_initial_sptr
        (new source_impl(serial, channel_mode, filename));
    }


    /*
     * The private constructor
     */
    source_impl::source_impl(std::string serial, int channel_mode, const std::string& filename)
      : gr::sync_block("source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {}

    /*
     * Our virtual destructor.
     */
    source_impl::~source_impl()
    {
    }

    int
    source_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    // Return io_signature to manage module output count
    // based on SISO (one output) and MIMO (two outputs) modes
    inline gr::io_signature::sptr source_impl::args_to_io_signature(int channel_number) {
      if (channel_number < 2) {
        return gr::io_signature::make(1, 1, sizeof(gr_complex));
      } else if (channel_number == 2) {
        return gr::io_signature::make(2, 2, sizeof(gr_complex));
      } else {
        std::cout << "ERROR: source_impl::args_to_io_signature(): channel_number must be 0,1 or 2."
          << std::endl;
        exit(0);
      }
    }

  } /* namespace limesdr */
} /* namespace gr */

