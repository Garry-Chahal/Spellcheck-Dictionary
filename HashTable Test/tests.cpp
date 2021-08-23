#include "catch.hpp"

// Uncomment to test private int nextPrime(int) function
//#define TEST_PRIVATE_METHODS

#ifdef TEST_PRIVATE_METHODS
#define private public
#endif


#include "HashTable.h"
#include "spellcheck.h"
#include <fstream>
#include <iostream>
#include <random>

using namespace std;

/**
 * @returns sorted vector
 */
vector<string> sVec( vector<string> vec )
{
    std::sort( vec.begin(), vec.end() );
    return vec;
}

TEST_CASE( "basic function test", "[HashTable]" )
{
    HashTable ht;

    ht.insert( "" );
    CHECK( ht.size() == 0 );
    CHECK( ht.find( "" ) == false );

    ht.insert( "human" );
    CHECK( ht.size() == 1 );
    CHECK( ht.find( "human" ) );

    ht.insert( "vulcan" );
    ht.insert( "andorian" );
    ht.insert( "ferengi" );
    ht.insert( "cardassian" );
    ht.insert( "vorta" );
    ht.insert( "klingon" );

    CHECK( ht.loadFactor() == 7.0 / 101 );
    CHECK( ht.size() == 7 );
    CHECK( ht.find( "vorta" ) );
    CHECK( ht.find( "klingon" ) );
    CHECK( ht.find( "vulcan" ) );
    CHECK( ht.find( "cardassian" ) );
    CHECK( ht.find( "andorian" ) );
    CHECK( ht.find( "ferengi" ) );

    ht.insert( "vulcan" );
    ht.insert( "andorian" );
    ht.insert( "ferengi" );
    ht.insert( "vulcan" );

    CHECK( ht.size() == 7 );
}

TEST_CASE( "resize tables test", "[HashTable]" )
{
    HashTable ht( 5 );
    CHECK( ht.maxSize() == 11 );

    ht.insert( "cardassian" );
    ht.insert( "human" );
    ht.insert( "andorian" );
    ht.insert( "klingon" );
    ht.insert( "ferengi" );
    ht.insert( "vulcan" );
    ht.insert( "vorta" );

    CHECK( ht.loadFactor() == 7.0 / 11 );
    CHECK( ht.size() == 7 );
    CHECK( ht.find( "cardassian" ) );
    CHECK( ht.find( "human" ) );
    CHECK( ht.find( "andorian" ) );
    CHECK( ht.find( "klingon" ) );
    CHECK( ht.find( "ferengi" ) );
    CHECK( ht.find( "vulcan" ) );
    CHECK( ht.find( "vorta" ) );

    ht.insert( "bajoran" ); // should trigger resize

    CHECK( ht.size() == 8 );
    CHECK( ht.maxSize() == 23 );

    CHECK( ht.find( "cardassian" ) );
    CHECK( ht.find( "human" ) );
    CHECK( ht.find( "andorian" ) );
    CHECK( ht.find( "klingon" ) );
    CHECK( ht.find( "ferengi" ) );
    CHECK( ht.find( "vulcan" ) );
    CHECK( ht.find( "vorta" ) );
    CHECK( ht.find( "bajoran" ) );


    ht.insert( "klingon" );
    ht.insert( "ferengi" );
    ht.insert( "vulcan" );

    ht.insert( "borg" );
    ht.insert( "romulan" );

    CHECK( ht.find( "klingon" ) );
    CHECK( ht.find( "ferengi" ) );
    CHECK( ht.find( "vulcan" ) );

    CHECK( ht.find( "borg" ) );
    CHECK( ht.find( "romulan" ) );

    CHECK( ht.size() == 10 );
}

TEST_CASE( "copy constructor test", "[RBT]" )
{
    HashTable ht1;

    ht1.insert( "resistor" );
    ht1.insert( "capacitor" );
    ht1.insert( "diode" );
    ht1.insert( "potentiometer" );
    CHECK( ht1.size() == 4 );

    HashTable ht2( ht1 );

    CHECK( ht2.size() == 4 );
    CHECK( ht2.find( "resistor" ) );
    CHECK( ht2.find( "capacitor" ) );
    CHECK( ht2.find( "diode" ) );
    CHECK( ht2.find( "potentiometer" ) );

    ht2.insert( "transistor" );
    ht2.insert( "inductor" );

    CHECK( ht2.size() == 6 );

    CHECK( ht2.find( "transistor" ) );
    CHECK( ht2.find( "inductor" ) );
    CHECK( ht1.find( "transistor" ) == false );
    CHECK( ht1.find( "inductor" ) == false );


    CHECK( ht1.size() == 4 );
    ht1.insert( "solenoid" );
    CHECK( ht1.size() == 5 );
    CHECK( ht1.find( "solenoid" ) );
    CHECK( ht2.find( "solenoid" ) == false );

    HashTable ht3;
    HashTable ht4( ht3 );
    CHECK( ht3.size() == 0 );
    CHECK( ht4.size() == 0 );

    ht4.insert( "solenoid" );
    ht4.insert( "capacitor" );

    CHECK( ht4.find( "solenoid" ) );
    CHECK( ht4.find( "capacitor" ) );
    CHECK( ht4.size() == 2 );
    CHECK( ht3.size() == 0 );
}

TEST_CASE( "assignment operator test", "[RBT]" )
{
    HashTable ht1( 5 );
    HashTable ht2( 1 );

    ht2 = ht1;

    CHECK( ht2.maxSize() == 11 );

    ht2.insert( "resistor" );
    ht2.insert( "capacitor" );
    CHECK( ht2.size() == 2 );

    ht1.insert( "op amp" );
    ht1.insert( "transistor" );
    ht1.insert( "fuse" );
    ht1.insert( "solenoid" );
    ht1.insert( "inductor" );
    CHECK( ht1.size() == 5 );

    ht1 = ht1;
    CHECK( ht1.size() == 5 );
    ht2 = ht1;
    CHECK( ht2.size() == 5 );

    CHECK( ht2.find( "op amp" ) );
    CHECK( ht2.find( "transistor" ) );
    CHECK( ht2.find( "fuse" ) );
    CHECK( ht2.find( "solenoid" ) );
    CHECK( ht2.find( "inductor" ) );

    ht2.insert( "potentiometer" );

    CHECK( ht2.find( "potentiometer" ) );
    CHECK( ht2.find( "fuse" ) );
    CHECK( ht2.find( "solenoid" ) );
    CHECK( ht1.find( "fuse" ) );
    CHECK( ht1.find( "solenoid" ) );
    CHECK( ht1.find( "potentiometer" ) == false );
    CHECK( ht1.size() == 5 );

    ht1 = ht2;
    CHECK( ht1.size() == 6 );
    CHECK( ht1.find( "op amp" ) );
    CHECK( ht1.find( "transistor" ) );
    CHECK( ht1.find( "inductor" ) );
    CHECK( ht1.find( "potentiometer" ) );

    ht2.insert( "diode" );
    ht2.insert( "led" );

    CHECK( ht2.size() == 8 );
    CHECK( ht2.find( "diode" ) );
    CHECK( ht2.find( "led" ) );
    CHECK( ht1.find( "diode" ) == false );
    CHECK( ht1.find( "led" ) == false );

    // assign after resize
    ht1 = ht2;

    CHECK( ht1.size() == 8 );
    CHECK( ht1.find( "op amp" ) );
    CHECK( ht1.find( "transistor" ) );
    CHECK( ht1.find( "inductor" ) );
    CHECK( ht1.find( "fuse" ) );
    CHECK( ht1.find( "potentiometer" ) );
    CHECK( ht1.find( "diode" ) );
    CHECK( ht1.find( "solenoid" ) );
    CHECK( ht1.find( "led" ) );
    CHECK( ht1.maxSize() == 23 );
}

TEST_CASE( "spellcheck extra letter test", "[SpellCheck]" )
{
    HashTable ht;

    ht.insert( "mazing" );
    ht.insert( "aazing" );
    ht.insert( "amzing" );
    ht.insert( "amaing" );
    ht.insert( "amazng" );
    ht.insert( "amazig" );
    ht.insert( "amazin" );
    ht.insert( "different" );
    ht.insert( "amazzing" );
    ht.insert( "aamazing" );
    ht.insert( "aamazingz" );

    CHECK( extraLetter( ht, "amazing" ) == sVec( {"mazing", "aazing", "amzing", "amaing", "amazng", "amazig", "amazin"} ) );

    ht.insert( "amazing" );
    CHECK( extraLetter( ht, "amazing" ) == ( vector<string> ) {"amazing"} );

    CHECK( extraLetter( ht, "other" ) == ( vector<string> ) {} );
}

TEST_CASE( "spellcheck transposition test", "[SpellCheck]" )
{
    HashTable ht;

    ht.insert( "bacdefg" );
    ht.insert( "acbdefg" );
    ht.insert( "abdcefg" );
    ht.insert( "abcedfg" );
    ht.insert( "abcdfeg" );
    ht.insert( "abcdegf" );
    ht.insert( "different" );
    ht.insert( "cabdefg" );
    ht.insert( "abcdfgh" );
    ht.insert( "abcdgef" );

    CHECK( transposition( ht, "abcdefg" ) == sVec( {"bacdefg", "acbdefg", "abdcefg", "abcedfg", "abcdfeg", "abcdegf"} ) );

    ht.insert( "abcdefg" );
    CHECK( transposition( ht, "abcdefg" ) == ( vector<string> ) {"abcdefg"} );

    CHECK( transposition( ht, "other" ) == ( vector<string> ) {} );
}

TEST_CASE( "spellcheck missing space test", "[SpellCheck]" )
{
    HashTable ht;

    ht.insert( "q" );
    ht.insert( "werty" );
    ht.insert( "qw" );
    ht.insert( "erty" );
    ht.insert( "qwe" );
    ht.insert( "rty" );
    ht.insert( "qwer" );
    ht.insert( "ty" );
    ht.insert( "qwert" );
    ht.insert( "y" );
    ht.insert( "different" );
    ht.insert( "qewrty" );
    ht.insert( "qe" );
    ht.insert( "wrty" );
    ht.insert( "" );
    ht.insert( "qewr" );

    CHECK( missingSpace( ht, "qwerty" ) == sVec( {"q werty", "qw erty", "qwe rty", "qwer ty", "qwert y"} ) );

    ht.insert( "qwerty" );
    CHECK( missingSpace( ht, "qwerty" ) == ( vector<string> ) {"qwerty"} );

    CHECK( missingSpace( ht, "other" ) == ( vector<string> ) {} );
}

TEST_CASE( "spellcheck missing letter test", "[SpellCheck]" )
{
    HashTable ht;

    ht.insert( "xword" );
    ht.insert( "wxord" );
    ht.insert( "woxrd" );
    ht.insert( "worxd" );
    ht.insert( "wordx" );
    ht.insert( "different" );
    ht.insert( "wrd" );
    ht.insert( "ward" );
    ht.insert( "lord" );

    CHECK( missingLetter( ht, "word" ) == sVec( {"xword", "wxord", "woxrd", "worxd", "wordx"} ) );

    ht.insert( "word" );
    CHECK( missingLetter( ht, "word" ) == ( vector<string> ) {"word"} );

    CHECK( missingLetter( ht, "other" ) == ( vector<string> ) {} );
}

TEST_CASE( "spellcheck incorrect letter test", "[SpellCheck]" )
{
    HashTable ht;

    ht.insert( "dord" );
    ht.insert( "lord" );
    ht.insert( "ward" );
    ht.insert( "wzrd" );
    ht.insert( "wodd" );
    ht.insert( "wori" );
    ht.insert( "woru" );
    ht.insert( "different" );
    ht.insert( "wrd" );

    CHECK( incorrectLetter( ht, "word" ) == sVec( {"dord", "lord", "ward", "wzrd", "wodd", "wori", "woru"} ) );

    ht.insert( "word" );
    CHECK( incorrectLetter( ht, "word" ) == ( vector<string> ) {"word"} );

    CHECK( incorrectLetter( ht, "other" ) == ( vector<string> ) {} );
}

TEST_CASE( "spellcheck based on wordlist test", "[SpellCheck]" )
{
    string filename = "wordlist1000.txt";
    ifstream fileStream( filename, ifstream::in );

    if( !fileStream.is_open() )
    {
        cout << "Unable to open file \"" << filename << "\"" << endl;
        return;
    }

    HashTable ht;
    string value;
    while( fileStream >> value )
        ht.insert( value );
    fileStream.close();

    CHECK( missingLetter( ht, "on" ) == sVec( {"on"} ) );
    CHECK( extraLetter( ht, "plant" ) == sVec( {"plant"} ) );

    CHECK( extraLetter( ht, "nort" ) == sVec( {"nor", "not"} ) );
    CHECK( transposition( ht, "atr" ) == sVec( {"art"} ) );
    CHECK( transposition( ht, "pateint" ) == sVec( {"patient"} ) );
    CHECK( missingSpace( ht, "rateat" ) == sVec( {"rate at"} ) );

    CHECK( missingLetter( ht, "sta" ) == sVec( {"star", "stay"} ) );
    CHECK( incorrectLetter( ht, "thed" ) == sVec( {"them", "then", "they"} ) );
}

string randomString( int length )
{
    static const char chars[] = "abcdefghijklmnopqrstuvwxyz";
    std::string s;
    s.reserve( length );
    for( int i = 0; i < length; ++i )
        s += chars[rand() % (sizeof( chars ) - 1)];
    return s;
}

TEST_CASE( "volume test", "[HashTable]" )
{
    const int stringsToInsert = 1000000;
    const int stringLength = 32;
    HashTable ht;
    cout << "Starting volume test, inserting " << stringsToInsert << " random strings, of length " << stringLength << endl;

    for( int i = 0; i < stringsToInsert; ++i )
    {
        string s = randomString( stringLength );
        ht.insert( s );
        CHECK( ht.find( s ) );
    }
    cout << "Done, HashTable size = " << ht.size() << ", maxSize = " << ht.maxSize() << endl;
}


#ifdef TEST_PRIVATE_METHODS
TEST_CASE( "private next prime test", "[HashTable]" )
{
    HashTable ht;

    CHECK( ht.nextPrime( 2 ) == 2 );
    CHECK( ht.nextPrime( 8 ) == 11 );
    CHECK( ht.nextPrime( 43 ) == 43 );
    CHECK( ht.nextPrime( 64 ) == 67 );
    CHECK( ht.nextPrime( 100 ) == 101 );
    CHECK( ht.nextPrime( 200 ) == 211 );
}

#endif