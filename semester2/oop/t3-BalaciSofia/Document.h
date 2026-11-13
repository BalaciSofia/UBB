//
// Created by balac on 5/29/2025.
//

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

class Document {
private:
    std::string name;//unique
    std::string keywords;
    std::string content;
    public:
    Document(std::string name, std::string keywords,std::string content);
    Document()= default;
    std::string getName();
    std::string getKeywords();
    std::string getContent();
    void setName(std::string name);
    void setContent(std::string content);
    void setKeywords(std::string keywords);
    friend std::istream& operator>>(std::istream& is,Document& doc);
};



#endif //DOCUMENT_H
