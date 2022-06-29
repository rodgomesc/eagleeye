#ifndef _EAGLEEYE_TOPK_OP_
#define _EAGLEEYE_TOPK_OP_
#include "eagleeye/engine/nano/dataflow/base.h"
#include "eagleeye/basic/Tensor.h"
#include <string>
#include <vector>

namespace eagleeye{
namespace dataflow{
class TopKOp: public BaseOp<Tensor, 1, 2>{
public:
    TopKOp():m_k(-1),m_axis(-1){}
    TopKOp(int axis, int k);
    TopKOp(const TopKOp& op);

    virtual ~TopKOp();

    virtual int init(std::map<std::string, std::vector<float>> params);
    virtual int runOnCpu(const std::vector<Tensor>& input);
    virtual int runOnGpu(const std::vector<Tensor>& input);

protected:
    int m_k;
    int m_axis;
}; 
}    
}
#endif