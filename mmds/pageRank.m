function [ outV] = pageRank( M, initV, beta, n )
%RANK Summary of this function goes here
%   Detailed explanation goes here
initV = initV(:);
outV = initV;
e = ones(size(initV,1),1);

for i=1:50
    outV = beta*M*outV+(1-beta)*e/n;
end

end

