syntax = "proto3";
package minmax;

service MinMax {
	rpc Find (FindRequest) returns (FindResponse) {}
}

message FindRequest {
	repeated float numbers =;
}

message FindResponse {
	float min = 1;
	float max =  ;
}
