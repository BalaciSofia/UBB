//
// Created by balac on 5/29/2025.
//

#include "Document.h"
#include <sstream>

Document::Document(std::string name,std::string keywords,std::string content):name(name),
keywords(keywords),content(content){
}

std::string Document::getName() {
    return name;
}

std::string Document::getKeywords() {
    return keywords;
}

std::string Document::getContent() {
    return content;
}

void Document::setName(std::string name) {
    this->name = name;
}

void Document::setContent(std::string content) {
    this->content = content;
}

void Document::setKeywords(std::string keywords) {
    this->keywords = keywords;
}
std::istream& operator>>(std::istream& is, Document& doc) {
    if (is.peek() == '\n') is.ignore();
    std::string str;
    std::getline(is, str);
    if (str.empty()) return is;
    std::istringstream iss(str);
    std::string a, b, c;
    std::getline(iss, a, '|');
    std::getline(iss, b, '|');
    std::getline(iss, c, '|');
    // a=name, b=keywords, c=content
    doc.setName(a);
    doc.setKeywords(b);
    doc.setContent(c);
    return is;
}