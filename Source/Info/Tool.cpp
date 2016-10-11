#include "Info.hpp"

#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

bool Tool::Parse(const YAML::Node &node) {
    if (node["Name"]) {
        m_Name = node["Name"].as<std::string>();
    }
    else {
        std::cerr << "Tool missing name." << std::endl;
        return false;
    }

    if (node["Type"]) {
        std::string type = node["Type"].as<std::string>();
        if (type == "Compiler") m_Type = Type::Compiler;
        else if (type == "Linker") m_Type = Type::Linker;
        else if (type == "Shell") m_Type = Type::Shell;
        else {
            std::cerr << "Tool has invalid type." << std::endl;
            return false;
        }
    }
    else {
        std::cerr << "Tool missing type." << std::endl;
        return false;
    }

    if (node["Platforms"]) {
        auto nodePlatform = node["Platforms"];
        for (auto it = nodePlatform.begin(); it != nodePlatform.end(); it++) {
            auto inner = *it;
            for (auto i = inner.begin(); i != inner.end(); i++) {
                std::string name = i->first.as<std::string>();
                std::string command = i->second.as<std::string>();
                m_Platforms[name] = command;
            }
        }
    }
    else {
        std::cerr << "Tool missing platforms." << std::endl;
        return false;
    }

    return true;
}