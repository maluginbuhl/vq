// Copyright (c) 2012-2014 Eric M. Heien, Michael K. Sachs, John B. Rundle
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include "GreensFileOutput.h"
#include "SimError.h"
#include <fstream>

void GreensFileOutput::initDesc(const SimFramework *_sim) const {
    const VCSimulation          *sim = static_cast<const VCSimulation *>(_sim);

    sim->console() << "# Greens output file: " << sim->getGreensOutfile() << std::endl;
}

/*!
 Writes Greens function values to the specified file.
 This is written to an HDF5 style file, so multiple processes
 can write in parallel.
 */
void GreensFileOutput::init(SimFramework *_sim) {
    VCSimulation            *sim = static_cast<VCSimulation *>(_sim);
    std::string             file_name = sim->getGreensOutfile();
    unsigned int            green_dim;
    BlockID                 row, col, global_row;
    double                  *shear_vals, *norm_vals;
    HDF5GreensDataWriter    *h5_greens_data;

    // Open the file
    green_dim = sim->numGlobalBlocks();
    h5_greens_data = new HDF5GreensDataWriter(file_name, green_dim);

    // Record the Greens function values
    shear_vals = new double[green_dim];
    norm_vals = new double[green_dim];

    for (row=0; row<sim->numLocalBlocks(); ++row) {
        global_row = sim->getGlobalBID(row);

        for (col=0; col<green_dim; ++col) {
            shear_vals[col] = sim->getGreenShear(global_row, col);
            norm_vals[col] = sim->getGreenNormal(global_row, col);
        }

        h5_greens_data->setGreensVals(global_row, shear_vals, norm_vals);
    }

    delete shear_vals;
    delete norm_vals;
    delete h5_greens_data;
}
