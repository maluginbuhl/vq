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

#include "VCSimulation.h"
#include "HDF5Data.h"

#ifndef _CHECKPOINT_FILE_OUTPUT_H_
#define _CHECKPOINT_FILE_OUTPUT_H_

/*!
 Dump the current simulation state to a file.
 */
class CheckpointFileOutput : public SimPlugin {
    private:
        unsigned int        checkpoint_num;

        void writeCheckpoint(const std::string &ckpt_file_name, const VCSimulation *sim);

    public:
        virtual std::string name(void) const {
            return "Checkpointing";
        }
        virtual void initDesc(const SimFramework *_sim) const;

        virtual void init(SimFramework *_sim) {
            checkpoint_num = 0;
        };
        virtual bool needsTimer(void) const {
            return true;
        };
        virtual SimRequest run(SimFramework *_sim);
        virtual void finish(SimFramework *_sim);
};

#endif
