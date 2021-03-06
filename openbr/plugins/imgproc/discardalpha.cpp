/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright 2012 The MITRE Corporation                                      *
 *                                                                           *
 * Licensed under the Apache License, Version 2.0 (the "License");           *
 * you may not use this file except in compliance with the License.          *
 * You may obtain a copy of the License at                                   *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 * Unless required by applicable law or agreed to in writing, software       *
 * distributed under the License is distributed on an "AS IS" BASIS,         *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 * See the License for the specific language governing permissions and       *
 * limitations under the License.                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <opencv2/imgproc/imgproc.hpp>

#include <openbr/plugins/openbr_internal.h>

using namespace cv;

namespace br
{

/*!
 * \ingroup transforms
 * \brief Drop the alpha channel (if exists).
 * \author Austin Blanton \cite imaus10
 */
class DiscardAlphaTransform : public UntrainableTransform
{
    Q_OBJECT

    void project(const Template &src, Template &dst) const
    {
        if (src.m().channels() > 4 || src.m().channels() == 2) {
            dst.file.fte = true;
            return;
        }

        dst = src;
        if (src.m().channels() == 4) {
            std::vector<Mat> mv;
            split(src, mv);
            mv.pop_back();
            merge(mv, dst);
        }
    }
};

BR_REGISTER(Transform, DiscardAlphaTransform)

} // namespace br

#include "imgproc/discardalpha.moc"
