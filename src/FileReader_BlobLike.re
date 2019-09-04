open FileReader_Types;

module Make = (M: {type t;}) => {
  [@bs.get] external size: M.t => float = "size";
  [@bs.get] external type_: M.t => string = "type";

  [@bs.send] external slice: M.t => blob = "slice";

  [@bs.send] external slice1: (M.t, ~start: int) => blob = "slice";

  [@bs.send] external slice2: (M.t, ~start: int, ~end_: int) => blob = "slice";

  [@bs.send]
  external slice3: (M.t, ~start: int, ~end_: int, ~contentType: string) => blob =
    "slice";
};