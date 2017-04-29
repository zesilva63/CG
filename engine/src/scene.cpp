#include <GL/glut.h>
#include "scene.h"
#include "model.h"

using tinyxml2::XMLDocument;
using tinyxml2::XMLNode;
using tinyxml2::XMLElement;

using std::vector;

void Scene::render() {
    for(Group *grp: groups)
        grp->render();
}

void Scene::parse(std::string filename) {
    XMLDocument doc;
    XMLNode *node; doc.LoadFile(filename.c_str());
    if ((node = doc.FirstChild())){
        node = node->FirstChild();
    }

    for(; node; node = node->NextSibling()) {
        if (!strcmp(node->Value(), "group")) {
            Group *grp = parse_group(node);
            groups.push_back(grp);
        }
    }
}

Group* Scene::parse_group(XMLNode *group_node) {
    Group *grp = new Group();
    XMLNode *node = group_node->FirstChild();
    for(; node; node = node->NextSibling()) {
        if (!strcmp(node->Value(), "ImediateTranslate"))
            parse_ImediateTranslate(grp, node);
        else if (!strcmp(node->Value(), "ImediateRotate"))
            parse_ImediateRotate(grp, node);
        else if (!strcmp(node->Value(), "models"))
            parse_models(grp, node);
        else if (!strcmp(node->Value(), "scale"))
            parse_scale(grp, node);
        else if (!strcmp(node->Value(), "translate"))
            parse_translate(grp, node);
        else if (!strcmp(node->Value(), "rotate"))
            parse_rotate(grp, node);
        else if (!strcmp(node->Value(), "group")) {
            Group *child = parse_group(node);
            grp->add_child(child);
        }
    }

    return grp;
}

void Scene::parse_models(Group* grp, XMLNode *nd) {
    XMLNode *model = nd->FirstChild();

    for(; model; model = model->NextSibling()) {
        XMLElement *elem = model->ToElement();

        if (!strcmp(model->Value(), "model"))
            parse_model(grp, elem);
    }
}

void Scene::parse_model(Group* grp, XMLNode *nd) {
    Model *model = new Model();

    model->parse(nd->ToElement());
    grp->add_model(model);
}

void Scene::parse_ImediateTranslate(Group* grp, XMLNode *nd) {
    Translation *tr = new Translation();

    tr->parse(nd->ToElement());
    grp->add_operation(tr);
}

void Scene::parse_ImediateRotate(Group* grp, XMLNode *nd) {
    Rotation *rt = new Rotation();

    rt->parse(nd->ToElement());
    grp->add_operation(rt);
}

void Scene::parse_scale(Group* grp, XMLNode *nd) {
    Scaling *sc = new Scaling();

    sc->parse(nd->ToElement());
    grp->add_operation(sc);
}

void Scene::parse_translate(Group* grp, XMLNode *nd) {
    XMLNode *model = nd->FirstChild();
    Translate *tr = new Translate();
    tr->parse(nd->ToElement());
    
    for(; model; model = model->NextSibling()) {
        XMLElement *elem = model->ToElement();

        if (!strcmp(model->Value(), "point"))
            tr->add_point(elem);
    }
    grp->add_translate(tr);
}

void Scene::parse_rotate(Group* grp, XMLNode *nd) {
    Rotate *rt = new Rotate();

    rt->parse(nd->ToElement());
    grp->add_rotate(rt);
}
