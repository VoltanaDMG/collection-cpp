/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Finanz Informatik. All rights reserved.
 *  Licensed under the MIT License. See License.txt in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
// example_prog.cpp - Clazz Initialization
#include <algorithm>
/// [StorageAPI]
#include "storage/Storage.hpp"
// Use normally
//#include <storage/Storage.hpp>

using namespace Storage;

std::vector<std::string> explode(const std::string& str, const char& ch) {
    std::string next;
    std::vector<std::string> result;

    // For each character in the string
    for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (!next.empty())
         result.push_back(next);
    return result;
}

int main(int argc, char const *argv[]) {
    /// [BEGIN] -> Storage
    // Make data for cache
    shared_ptr<StorageItem>fld3_1=shared_ptr<StorageItem>(new StorageItem());
    fld3_1->fldno=1;
    fld3_1->descriptor="A packager name";
    fld3_1->value="F0F0";
    shared_ptr<StorageItem>fld3_2=shared_ptr<StorageItem>(new StorageItem());
    fld3_2->fldno=2;
    fld3_2->descriptor="A packager name";
    fld3_2->value="F0F0";
    shared_ptr<StorageItem>fld3_3=shared_ptr<StorageItem>(new StorageItem());
    fld3_3->fldno=3;
    fld3_3->descriptor="A packager name";
    fld3_3->value="F0F0";
    shared_ptr<StorageItem>fld4=shared_ptr<StorageItem>(new StorageItem());
    fld4->fldno=4;
    fld4->descriptor="A packager name";
    fld4->value="F0F0F0F0F0F0";
    shared_ptr<StorageItem>fld5=shared_ptr<StorageItem>(new StorageItem());
    fld5->fldno=5;
    fld5->descriptor="A packager name";
    fld5->value="F0F1F0F0";
    shared_ptr<StorageItem>fld48_61_3=shared_ptr<StorageItem>(new StorageItem());
    fld48_61_3->fldno=3;
    fld48_61_3->descriptor="A packager name";
    fld48_61_3->value="F0F1F0F0";
    // Create cache as string->StorageItem store.  Add data
    StorageManager::INSTANCE()->cache.set("3.1",fld3_1);
    StorageManager::INSTANCE()->cache.set("3.2",fld3_2);
    StorageManager::INSTANCE()->cache.set("3.3",fld3_3);
    StorageManager::INSTANCE()->cache.set("4",fld4);
    StorageManager::INSTANCE()->cache.set("5",fld5);
    StorageManager::INSTANCE()->cache.set("48.61.3",fld48_61_3);
    // Fetch back
    boost::shared_ptr<StorageItem>out=StorageManager::INSTANCE()->cache.get("3.1");
    printf("%d:%s    %s\n",out->fldno,out->descriptor.c_str(),out->value.c_str());
    /// [END] -> Storage
    /// [BEGIN] -> Storage - KeySet
    std::vector<std::string> keys = StorageManager::INSTANCE()->cache.keySet();
    struct {
        bool operator()(std::string lhs, std::string rhs) {
            std::vector<std::string> lhsArr = explode(lhs, '.');
            std::vector<std::string> rhsArr = explode(rhs, '.');

            if (std::atoi(lhsArr[0].c_str()) == std::atoi(rhsArr[0].c_str())) {
                if (std::atoi(lhsArr[1].c_str()) == std::atoi(rhsArr[1].c_str())) {
                    if (std::atoi(lhsArr[2].c_str()) == std::atoi(rhsArr[2].c_str()))
                        return std::atoi(lhsArr[3].c_str()) < std::atoi(rhsArr[3].c_str());
                    return std::atoi(lhsArr[2].c_str()) < std::atoi(rhsArr[2].c_str());
                }
                return std::atoi(lhsArr[1].c_str()) < std::atoi(rhsArr[1].c_str());
            }
            return std::atoi(lhsArr[0].c_str()) < std::atoi(rhsArr[0].c_str());
        }
    } atoiComp;
    std::sort(keys.begin(), keys.end(), atoiComp);
    for (std::string key : keys)
        printf("[Key] %s\n", key.c_str());
    /// [END] -> Storage - KeySet
    return 0;
}