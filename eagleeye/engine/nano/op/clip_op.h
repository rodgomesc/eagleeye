#ifndef _EAGLEEYE_CLIP_OP_
#define _EAGLEEYE_CLIP_OP_

#include "eagleeye/engine/nano/dataflow/base.h"
#include "eagleeye/basic/Tensor.h"
#include <string>
#include <vector>

namespace eagleeye{
namespace dataflow{
class ClipOp:public BaseOp<Tensor, 1, 1>{
public:
    ClipOp(){}
    ClipOp(float min_v=0.0f, float max_v=1.0f);
    ClipOp(const ClipOp& op);
    virtual ~ClipOp();

    virtual int init(std::map<std::string, std::vector<float>> params);
    virtual int runOnCpu(std::vector<Tensor> input={});
    virtual int runOnGpu(std::vector<Tensor> input={});

protected:
    float m_min_v;
    float m_max_v;
};
}
}

#endif