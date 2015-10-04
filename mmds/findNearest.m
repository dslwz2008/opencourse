function [ n1,n2 ] = findNearest( a,b,v )
%FINDNEAREST Summary of this function goes here
%   Detailed explanation goes here

dist_av1=norm(a-v,1);
dist_bv1=norm(b-v,1);
if dist_av1<dist_bv1
    n1 = 1;
else
    n1 = 2;
end

dist_av2=norm(a-v);
dist_bv2=norm(b-v);
if dist_av2<dist_bv2
    n2 = 1;
else
    n2 = 2;
end

end

