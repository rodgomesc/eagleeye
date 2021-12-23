#ifndef _EAGLEEYE_CONSTNODE_H_
#define _EAGLEEYE_CONSTNODE_H_
#include "eagleeye/common/EagleeyeMacro.h"
#include "eagleeye/framework/pipeline/AnyNode.h"
#include "eagleeye/framework/pipeline/SignalFactory.h"


namespace eagleeye
{
class ConstNode:public AnyNode{
public:
    typedef ConstNode               Self;
    typedef AnyNode             Superclass;

    /**
	 *	@brief Get class identity
	 */
    EAGLEEYE_CLASSIDENTITY(ConstNode);

    /**
     *  @brief constructor/destructor
     */
    ConstNode(int input_port_num, std::vector<AnySignal*> output_const_sigs);
    virtual ~ConstNode();

    virtual void executeNodeInfo();

private:
    ConstNode(const ConstNode&);
    void operator=(const ConstNode&);
};
} // namespace eagleeye

#endif