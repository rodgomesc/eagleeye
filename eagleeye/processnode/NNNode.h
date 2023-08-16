#ifndef _EAGLEEYE_NNNODE_H_
#define _EAGLEEYE_NNNODE_H_
#include "eagleeye/common/EagleeyeMacro.h"
#include "eagleeye/framework/pipeline/AnyNode.h"
#include "eagleeye/basic/Matrix.h"
#include "eagleeye/basic/Array.h"
// #include "eagleeye/engine/nano/op/placeholder.h"
// #include "eagleeye/engine/nano/dataflow/node_impl_asyn.hpp"
// #include "eagleeye/engine/nano/dataflow/asyn.hpp"
#include "eagleeye/engine/nano/dataflow/graph.hpp"
#include "eagleeye/common/CJsonObject.hpp"
#include<functional>
#include "eagleeye/framework/pipeline/DynamicNodeCreater.h"


namespace eagleeye{

typedef std::function<bool(dataflow::Graph* g, std::string op_name, std::string op_cls, neb::CJsonObject op_config, dataflow::Node*&, std::string resource_folder)> OpBFuncType;
class NNNode:public AnyNode, DynamicNodeCreator<NNNode>{
public:    
    typedef NNNode                  Self;
    typedef AnyNode                 Superclass;

    NNNode();
    virtual ~NNNode();

    /**
	 *	@brief Get class identity
	 */
	EAGLEEYE_CLASSIDENTITY(NNNode);

    /**
	 * @brief execute control
	 * 
	 */
	virtual void executeNodeInfo();

    /**
     * @brief 获得计算图，外部硬写入处理流水线
     * 
     */
    dataflow::Graph* getOpGraph(){return this->m_g;};

    /**
     * @brief 分析计算图
     */
    void analyze(std::vector<std::string> in_ops, std::vector<std::pair<std::string, int>> out_ops);

    /**
     * @brief 得到计算图的输入
     */
    int getOpGraphIn();

    /**
     * @brief 自动加载算子结构
     * 
     * @param nn_info 
     * @return true 
     * @return false 
     */
    bool load(neb::CJsonObject nn_info, OpBFuncType op_builder, std::string resource_folder);

    /**
     * @brief Set the Output Signal Type object
     * 
     * @param port 
     * @param type 
     */
    void makeOutputSignal(int port, std::string type_str);

    void setModelFolder(const std::string model_folder);
    void getModelFolder(std::string& model_folder);

    void setWritableFolder(const std::string writable_folder);
    void getWritableFolder(std::string& writable_folder);

private:
    NNNode(const NNNode&);
    void operator=(const NNNode&);

    dataflow::Graph* m_g;
    std::map<int, std::string> m_input_map;
    std::map<int, std::pair<std::string, int>> m_output_map;

    bool m_is_init;
};
}
#endif