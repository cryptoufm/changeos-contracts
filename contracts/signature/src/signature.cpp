#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <set>
#define DEBUG

#include "logger.hpp"
#include "signature.hpp"

using namespace eosio;
using namespace std;

class Signature {
    public:
        Signature() {}
        Signature(std::string volunteerid, std::string imagehash) : volunteerid(volunteerid), imagehash(imagehash) {}
        std::string volunteerid;
        std::string imagehash; 
};


class vote : public eosio::contract {

    public:
        using contract::contract;

        std::map<std::string, Signature> registry; 

        void addsignature( string volunteerid, string citizenuid, string imagehash ) {
            print( "DPI received: ", volunteerid, citizenuid, imagehash );
            if (verifydpi(citizenuid)) {
                logger_info( "SUCCESS: DPI added: ", citizenuid);
                registry.insert(std::map<std::string, Signature>::value_type(citizenuid, Signature(volunteerid,imagehash)));
            
                // for(map<std::string, Signature >::const_iterator it = registry.begin();
                //     it != registry.end(); ++it)
                // {
                //     std::cout << it->first << " " << it->second.first << " " << it->second.second << "\n";
                // }
                std::map<std::string, Signature>::iterator pos;

                for (pos = registry.begin(); pos != registry.end(); ++pos){
                    
                    print(pos -> first);
                    // cout << "key: \"" << pos -> first << "\" "
                    //      << "values : " << pos -> second.volunteerid << 
                    //      << "values : " << pos -> second.imagehash << endl;
                }

            } 
            else {
                logger_info( "FAILED: DPI not added: ", citizenuid);
            }
        }

        bool verifydpi( string dpi ) {
            print( "DPI received in VERIFYDPI" );

            std::map<std::string, Signature>::iterator found; 
            found = registry.find(dpi);
    
            if (found == registry.end()) {
                return true;
            }
            else {
                return false;
            }
       }

};

EOSIO_ABI( vote, (addsignature) )
