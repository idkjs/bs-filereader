module Make = (M: {type t;}) => {
  [@bs.get] external size: M.t => float = "size";
  [@bs.get] external type_: M.t => string = "type";

  [@bs.send] external slice_: M.t => FileReader__.blob = "slice";

  [@bs.send]
  external sliceWithStart: (M.t, int) => FileReader__.blob = "slice";

  [@bs.send]
  external sliceWithStartEnd: (M.t, int, int) => FileReader__.blob = "slice";

  [@bs.send]
  external slice:
    (M.t, ~start: int, ~end_: int, ~contentType: string) => FileReader__.blob =
    "slice";
};