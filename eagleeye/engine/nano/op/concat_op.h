#ifndef _EAGLEEYE_CONCAT_OP_H_
#define _EAGLEEYE_CONCAT_OP_H_

#include "eagleeye/engine/nano/dataflow/base.h"
#include "eagleeye/basic/Tensor.h"
#include <string>
#include <vector>

namespace eagleeye{
namespace dataflow{
class ConcatOp:public BaseOp<Tensor, 2, 1>{
public:
    ConcatOp(){}
    ConcatOp(int aixs);
    ConcatOp(const ConcatOp& op);
    virtual ~ConcatOp();

    virtual int init(std::map<std::string, std::vector<float>> params);
    virtual int runOnCpu(std::vector<Tensor> input={});
    virtual int runOnGpu(std::vector<Tensor> input={});

protected:
    int m_aixs;
};
}
}

#endif