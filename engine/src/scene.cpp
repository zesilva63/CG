#include <GL/glut.h>
#include "scene.h"
#include "model.h"

using tinyxml2::XMLDocument;
using tinyxml2::XMLNode;
using tinyxml2::XMLElement;

using std::vector;

Group* parse_group(XMLNode *nd);
void parse_model(Group* grp, XMLNode *nd);
void parse_scale(Group* grp, XMLNode *nd);
void parse_models(Group* grp, XMLNode *nd);
void parse_rotate(Group* grp, XMLNode *nd);
void parse_translate(Group* grp, XMLNode *nd);

void Scene::render() {
    for(Group *grp: groups)
        grp->render();
}

void Scene::parse(std::string filename) {
    XMLDocument doc;
    XMLNode *node; doc.LoadFile(filename.c_str());

    if ((node = doc.FirstChild()))
        node = node->FirstChild();

    for(; node; node = node->NextSibling()) {
        if (!strcmp(node->Value(), "group")) {
            Group *grp = parse_group(node);
            groups.push_back(grp);
        }
    }
}

Group* parse_group(XMLNode *group_node) {
    Group *grp = new Group();
    XMLNode *node = group_node->FirstChild();

    for(; node; node = node->NextSibling()) {
        if (!strcmp(node->Value(), "translate"))
            parse_translate(grp, node);
        else if (!strcmp(node->Value(), "rotate"))
            parse_rotate(grp, node);
        else if (!strcmp(node->Value(), "models"))
            parse_models(grp, node);
        else if (!strcmp(node->Value(), "scale"))
            parse_scale(grp, node);
        else if (!strcmp(node->Value(), "group")) {
            Group *child = parse_group(node);
            grp->add_child(child);
        }
    }

    return grp;
}

void parse_models(Group* grp, XMLNode *nd) {
    XMLNode *model = nd->FirstChild();

    if (grp->has_models())
        throw std::domain_error("A group can only have a single tag models");

    for(; model; model = model->NextSibling()) {
        XMLElement *elem = model->ToElement();

        if (!strcmp(model->Value(), "model"))
            parse_model(grp, elem);
    }
}

void parse_model(Group* grp, XMLNode *nd) {
    XMLElement *elm = nd->ToElement();
    const char* filename = elm->Attribute("file");
    Model *model = new Model();

    model->parse(filename);
    grp->add_model(model);
}

void parse_translate(Group* grp, XMLNode *nd) {
    if (grp->has_models())
        throw std::domain_error("Geometric transformations should be specified before models");

    if (grp->has_operation("translation"))
        throw std::domain_error("There must be only a geometric transformation of the same type inside a group");

    Translation *tr = new Translation();
    tr->parse(nd->ToElement());
    grp->add_operation(tr);
}

void parse_rotate(Group* grp, XMLNode *nd) {
    if (grp->has_models())
        throw std::domain_error("Geometric transformations should be specified before models");

    if (grp->has_operation("rotation"))
        throw std::domain_error("There must be only a geometric transformation of the same type inside a group");

    Rotation *rt = new Rotation();
    rt->parse(nd->ToElement());
    grp->add_operation(rt);
}

void parse_scale(Group* grp, XMLNode *nd) {
    if (grp->has_models())
        throw std::domain_error("Geometric transformations should be specified before models");

    if (grp->has_operation("scaling"))
        throw std::domain_error("There must be only a geometric transformation of the same type inside a group");

    Scaling *sc = new Scaling();
    sc->parse(nd->ToElement());
    grp->add_operation(sc);
}
