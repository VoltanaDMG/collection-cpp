/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Finanz Informatik. All rights reserved.
 *  Licensed under the Apache-2.0 License. See License.txt in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
// StorageManager.hpp - Header Definition incl. Initialization
#ifndef _STORAGEAPI_STORAGEMANAGER_H_
#define _STORAGEAPI_STORAGEMANAGER_H_
#include "StorageCache.hpp"
#include "StorageItem.hpp"

namespace Storage {
    /** --- StorageManager ---
     * A manager which holds the cache system and make it accessible
     * for every other file. 
     * 
     * This prevents the user to create another cache system for this
     * program
     */
    class StorageManager {

        public:
            /** The only instance you need */
            static StorageManager* INSTANCE() {
                static CGuard g; //Speicherbereinigung
                if (!_instance)
                    _instance = new StorageManager();
                return _instance;
            }
            // Real storage holder
            Storage::StorageCache<std::string, Storage::StorageItem> cache;

        private:
            static StorageManager* _instance;
            /** Verhindert, dass ein Objekt von außerhalb von StorageManager erzeugt wird. */
            StorageManager() {}
            /** verhindert, dass eine weitere Instanz via Kopie-Konstruktor erstellt werden kann */
            StorageManager(const StorageManager&) {}
            ~StorageManager() {}

            class CGuard {
                public:
                    ~CGuard() {
                        if ( NULL != StorageManager::_instance) {
                            delete StorageManager::_instance;
                            StorageManager::_instance = NULL;
                        }
                    }
            };


    };
    /** Statische Elemente einer Klasse müssen initialisiert werden. */
StorageManager* StorageManager::_instance = 0;
};
#endif