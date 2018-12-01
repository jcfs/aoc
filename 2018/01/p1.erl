#!/usr/bin/env escript
-import(lists,[sum/1]).
%% -*- erlang -*-
main(_) ->
  {ok, File} = file:open("in",[read]),
  X = read(File),
  io:fwrite("~p~n",[sum(X)]).

read(File) ->
    case file:read_line(File) of
        {ok, Data} -> 
          {Data1, Rest} = string:to_integer(re:replace(Data, "(^\\s+)|(\\s+$)", "", [global,{return,list}])),
          [Data1 | read(File)];
        eof        -> []
    end.
