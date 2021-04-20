
#include "TVector3.h"

TVector3 Vertex(TVector3 p1, TVector3 b, TVector3 p2, TVector3 d){

    TVector3 d1, d2, n1, n2, c1, c2, rr;

    d1 = ( b - p1 ).Unit();
    d2 = ( d - p2 ).Unit();

    n1 = d1.Cross( d2.Cross(d1) );
    n2 = d2.Cross( d1.Cross(d2) );

    c1 = p1 + d1 * ( ( ( p2 - p1 ) * n2 ) / ( d1*n2 ) );
    c2 = p2 + d2 * ( ( ( p1 - p2 ) * n1 ) / ( d2*n1 ) );

    rr = (c1+c2)*0.5 ;

    return rr;
}

double Distance(TVector3 p1, TVector3 b, TVector3 p2, TVector3 d){

    TVector3 d1, d2, n1, n2, c1, c2, rr;

    d1 = ( b - p1 ).Unit();
    d2 = ( d - p2 ).Unit();

    n1 = d1.Cross( d2.Cross(d1) );
    n2 = d2.Cross( d1.Cross(d2) );

    c1 = p1 + d1 * ( ( ( p2 - p1 ) * n2 ) / ( d1*n2 ) );
    c2 = p2 + d2 * ( ( ( p1 - p2 ) * n1 ) / ( d2*n1 ) );

    return (c1-c2).Mag() ;
}

