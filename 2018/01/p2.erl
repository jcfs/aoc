#!/usr/bin/env escript
main(_) ->
  {ok, File} = file:open("in",[read]),
  S = sets:new(),
  sets:add_element(0, S),
  process_frequency(File, 0, S).

process_frequency(File, SUM, L) ->
    case file:read_line(File) of
        {ok, Data} -> 
          {Data1, _} = string:to_integer(re:replace(Data, "(^\\s+)|(\\s+$)", "", [global,{return,list}])),
          Frequency = SUM + Data1,
          Present = sets:is_element(Frequency, L),
          case Present of
            true -> io:fwrite("Frequency: ~p : ~p\n", [Frequency, Present]);
            false -> 
              L2 = sets:add_element(Frequency, L),
              [Data1 | process_frequency(File, Frequency, L2)]
          end;
        eof        -> 
          {ok, F} = file:open("in",[read]),
          process_frequency(F, SUM, L)
    end.

