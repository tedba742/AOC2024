-module(day1).
-export([day1/0]).

day1() ->
    {ok, Binary} = file:read_file("input.txt"),
    Lines = string:split(binary_to_list(Binary), "\n", all),
    Parsed = [parse_line(Line) || Line <- Lines],
    Pairs = [Pair || {ok, Pair} <- Parsed],

    Lefts = [A || {A, _} <- Pairs],
    Rights = [B || {_, B} <- Pairs],

    SortedLefts = lists:sort(Lefts),
    SortedRights = lists:sort(Rights),

    Distances = [abs(A - B) || {A, B} <- lists:zip(SortedLefts, SortedRights)],
    Total = lists:sum(Distances),

    io:format("Total distance: ~p~n", [Total]).

parse_line(Line0) ->
    Line = string:trim(Line0, trailing, "\r\n\t "),
    case string:tokens(Line, " \t") of
        [A_str, B_str] ->
            try
                {ok, {list_to_integer(A_str), list_to_integer(B_str)}}
            catch
                _:_ ->
                    io:format("Warning: bad line \"~s\"~n", [Line]),
                    skip
            end;
        _ ->
            io:format("Warning: malformed line \"~s\"~n", [Line]),
            skip
    end.

