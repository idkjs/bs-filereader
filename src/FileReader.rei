type t;

[@bs.get] [@bs.return nullable]
external error: t => option(Js.Json.t) = "error";

let result:
  t =>
  option([ | `String(string) | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)]);

[@bs.set] external onload: (t, Dom.event => unit) => unit = "onload";
[@bs.set] external onerror: (t, Dom.event => unit) => unit = "onerror";
[@bs.set] external onabort: (t, Dom.event => unit) => unit = "onabort";

[@bs.send] external abort: t => unit = "abort";

// constructor, avoid external
let make: unit => t;

[@bs.send]
external readAsArrayBuffer: (t, FileReader_Blob.t) => unit =
  "readAsArrayBuffer";

[@bs.send]
external readAsDataURL: (t, FileReader_Blob.t) => unit = "readAsDataURL";

[@bs.send]
external readAsText: (t, FileReader_Blob.t, ~encoding: string=?, unit) => unit =
  "readAsText";

exception FileReadError;

module File = FileReader_File;
module Blob = FileReader_Blob;

let toArrayBuffer: Blob.t => Js.Promise.t(Js.Typed_array.ArrayBuffer.t);

let toDataURL: Blob.t => Js.Promise.t(string);

let toText: (Blob.t, ~encoding: string=?, unit) => Js.Promise.t(string);
