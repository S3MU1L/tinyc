signed int    ui2si() { return -1u; }
signed int    uc2si() { return ( unsigned char ) -1; }
signed int    sc2si() { return ( signed char ) 255; }
unsigned int  si2ui() { return -1; }
unsigned int  sc2ui() { return ( signed char ) 255u; }
unsigned int  uc2ui() { return ( unsigned char ) -1; }
signed char   ui2sc() { return 1025u; }
signed char   si2sc() { return -515; }
signed char   uc2sc() { return ( unsigned char ) 255; }
unsigned char ui2uc() { return 1025u; }
unsigned char si2uc() { return -515; }
unsigned char sc2uc() { return ( signed char ) -1; }

int main()
{
    assert( ui2si() == -1 );
    assert( uc2si() == 255 );
    assert( sc2si() == -1 );
    assert( si2ui() == -1u );
    assert( sc2ui() == -1u );
    assert( uc2ui() == 255 );
    assert( ui2sc() == 1 );
    assert( si2sc() == -3 );
    assert( uc2sc() == -1u );
    assert( ui2uc() == 1 );
    assert( si2uc() == 253 );
    assert( sc2uc() == 255 );
    return 0;
}
