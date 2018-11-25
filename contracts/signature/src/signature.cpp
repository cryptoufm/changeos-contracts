#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <map>
#include <iterator>
#include <string>

#define DEBUG

#include "logger.hpp"
#include "signature.hpp"

using namespace eosio;
using namespace std;

class hello : public eosio::contract {

    public:
        using contract::contract;

        [[eosio::action]]
        void addSignature( string dpi ) {
            print( "DPI received: ", dpi );
            verifyDPI(dpi);
        }

        bool verifyDPI( string dpi ) {
            logger_info( "debug dpi: ", dpi);
            return true;
       }





};

EOSIO_ABI( hello, (addSignature) )
