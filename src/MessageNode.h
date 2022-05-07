/**
 * @file MessageNode.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#ifndef ICP_PROJECT_MESSAGE_NODE_H
#define ICP_PROJECT_MESSAGE_NODE_H

/**
 * Entity class for grouping message nodes of sequence diagram together
 */
class MessageNode
{
    /**
     * Name of the node
     */
    std::string name;

  protected:
    /**
     * Implicit constructor
     */
    MessageNode(): name{} {};

    /**
     * Constructor for initializing with known name
     *
     * @param name Name of the node
     */
    explicit MessageNode(std::string name): name{name} {};

    /**
     * Default virtual destructor for enable polymorphic behavior
     */
    virtual ~MessageNode() = default;

  public:
    /**
     * Getter for node name
     *
     * @return Node's name
     */
    std::string getName() const
    {
        return name;
    }

    /**
     * Setter for node name
     *
     * @param new_name New node name
     */
    void setName(const std::string& new_name)
    {
        name = new_name;
    }
};

#endif //ICP_PROJECT_MESSAGE_NODE_H
