/**
 * @file save-class-diagram.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include "../src/ClassDiagram.h"
#include "../src/Generalization.h"
#include "../src/FileClassDiagramRepository.h"

/**
 * Simple test for saving class diagram
 */
int main()
{
    ClassDiagram diagram{};

    Class electronicDevice{"ElectronicDevice", std::tuple<int, int>{10, 10}};
    electronicDevice.addAttribute(ClassAttribute{"price", AccessModifier::PROTECTED, "int"});
    electronicDevice.addAttribute(ClassAttribute{"color", AccessModifier::PROTECTED, "string"});
    diagram.addClass(electronicDevice);

    Class phone{"Phone", std::tuple<int, int>{410, 10}};
    phone.addAttribute(ClassAttribute{"batterySize", AccessModifier::PRIVATE, "int"});
    phone.addMethod(ClassMethod{"isValuable", AccessModifier::PUBLIC, std::vector<MethodParameter> {}, "bool"});
    phone.addMethod(ClassMethod{"setColor", AccessModifier::PUBLIC, std::vector<MethodParameter> {
            MethodParameter{"newColor", "string"}
    }});
    diagram.addClass(phone);

    Generalization phoneInheritsElectronicDevice{&phone, &electronicDevice};
    diagram.addRelationship(&phoneInheritsElectronicDevice);

    FileClassDiagramRepository repo{"examples/class-diagram-output.xml"};
    repo.saveDiagram(diagram);

    return 0;
}