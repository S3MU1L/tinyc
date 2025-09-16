signed int    ui2si() { unsigned int  x = -1u;   return x; }
signed int    uc2si() { unsigned char x = -1;    return x; }
signed int    sc2si() { signed char   x = 255;   return x; }
unsigned int  si2ui() { signed int    x = -1;    return x; }
unsigned int  sc2ui() { signed char   x = 255u;  return x; }
unsigned int  uc2ui() { unsigned char x = -1;    return x; }
signed char   ui2sc() { unsigned int  x = 1025u; return x; }
signed char   si2sc() { signed int    x = -515;  return x; }
signed char   uc2sc() { unsigned char x = 255;   return x; }
unsigned char ui2uc() { unsigned int  x = 1025u; return x; }
unsigned char si2uc() { signed int    x = -515;  return x; }
unsigned char sc2uc() { signed char   x = -1;    return x; }

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
