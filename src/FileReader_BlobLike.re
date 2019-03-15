module Make = (M: {type t;}) => {
  [@bs.get] external size: M.t => float = "size";
  [@bs.get] external type_: M.t => string = "type";

  [@bs.send]
  external slice:
    (M.t, ~start: int=?, ~end_: int=?, ~contentType: string=?, unit) =>
    FileReader__.blob =
    "slice";
};