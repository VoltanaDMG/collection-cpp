/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Finanz Informatik. All rights reserved.
 *  Licensed under the MIT License. See License.txt in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
// StorageItem.hpp - Header Definition incl. Initialization
#ifndef _STORAGEAPI_STORAGEITEM_H_
#define _STORAGEAPI_STORAGEITEM_H_
#include <string>

namespace Storage {
    class StorageItem {
        public:
            int fldno;
            std::string descriptor;
            std::string value;
    };
};
#endif