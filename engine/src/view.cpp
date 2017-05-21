#include <GL/glut.h>
#include "view.h"
#include "scale.h"
#include "rotate.h"
#include "translate.h"

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;

using std::vector;
using std::string;

static string base_name(string pathname);

void View::render() {
    for(Group *grp: groups)
        grp->render();
}

void View::render_lights() {
    for(Light *l: lights)
        l->definePos();
}


void View::parse(string filename) {
    XMLDocument doc;
    XMLNode *node;

    dirname = base_name(filename);
    doc.LoadFile(filename.c_str());

    if ((node = doc.FirstChild()))
        node = node->FirstChild();

    for(; node; node = node->NextSibling()) {
        if (!strcmp(node->Value(), "group")) {
            Group *grp = parse_group(node);
            groups.push_back(grp);
        }
        if (!strcmp(node->Value(), "lights")) {
            parse_lights(node);
        }
    }
}

Group* View::parse_group(XMLNode *group_node) {
    Group *grp = new Group();
    XMLNode *node = group_node->FirstChild();
    for(; node; node = node->NextSibling()) {
        if (!strcmp(node->Value(), "models"))
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

void View::parse_lights(XMLNode *light_node) {
    XMLNode *light = light_node->FirstChild();

    for(; light; light = light->NextSibling()) {
        XMLElement *elem = light->ToElement();

        if (!strcmp(elem->Value(), "light")) {
            Light *light = new Light();
            light->parse(elem);

            lights.push_back(light);
        }
    }
}

void View::parse_models(Group* grp, XMLNode *nd) {
    XMLNode *model = nd->FirstChild();

    for(; model; model = model->NextSibling()) {
        XMLElement *elem = model->ToElement();

        if (!strcmp(model->Value(), "model"))
            parse_model(grp, elem);
    }
}

void View::parse_model(Group* grp, XMLNode *nd) {
    Model *model = new Model();

    model->parse(dirname, nd->ToElement());
    grp->add_model(model);
}

void View::parse_scale(Group* grp, XMLNode *nd) {
    Scale *sc = new Scale();

    sc->parse(nd->ToElement());
    grp->add_operation(sc);
}

void View::parse_translate(Group* grp, XMLNode *nd) {
    Translate *tr = new Translate();
    tr->parse(nd->ToElement());

    XMLNode *point = nd->FirstChild();
    while(point) {
        XMLElement *p = point->ToElement();

        if (!strcmp(point->Value(), "point"))
            tr->add_point(p);

        point = point->NextSibling();
    }

    grp->add_operation(tr);
}

void View::parse_rotate(Group* grp, XMLNode *nd) {
    Rotate *rt = new Rotate();

    rt->parse(nd->ToElement());
    grp->add_operation(rt);
}

static string base_name(string pathname) {
    std::size_t found = pathname.find_last_of("/\\");
    return string(pathname, 0, found+1);
}
