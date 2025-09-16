signed int    ui2si( unsigned int x )  { return -1u; }
signed int    uc2si( unsigned char x ) { return ( unsigned char ) -1; }
signed int    sc2si( signed char x )   { return ( signed char ) 255; }
unsigned int  si2ui( signed int x )    { return -1; }
unsigned int  sc2ui( signed char x )   { return ( signed char ) 255u; }
unsigned int  uc2ui( unsigned char x ) { return ( unsigned char ) -1; }
signed char   ui2sc( unsigned int x )  { return 1025u; }
signed char   si2sc( signed int x )    { return -515; }
signed char   uc2sc( unsigned char x ) { return ( unsigned char ) 255; }
unsigned char ui2uc( unsigned int x )  { return 1025u; }
unsigned char si2uc( signed int x )    { return -515; }
unsigned char sc2uc( signed char x )   { return ( signed char ) -1; }

int main()
{
    assert( ui2si( -1u )   == -1 );
    assert( uc2si( -1 )    == 255 );
    assert( sc2si( 255 )   == -1 );
    assert( si2ui( -1 )    == -1u );
    assert( sc2ui( 255u )  == -1u );
    assert( uc2ui( -1 )    == 255 );
    assert( ui2sc( 1025u ) == 1 );
    assert( si2sc( -515 )  == -3 );
    assert( uc2sc( 255 )   == -1u );
    assert( ui2uc( 1025u ) == 1 );
    assert( si2uc( -515 )  == 253 );
    assert( sc2uc( -1 )    == 255 );
    return 0;
}
