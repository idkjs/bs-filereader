open FileReader_Types;

type t;

[@bs.get] [@bs.return nullable]
external error: t => option(Js.Json.t) = "error";

[@bs.get] external result_: t => Js.Json.t = "result";

let result:
  t =>
  option([ | `String(string) | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)]) =
  self => {
    let value = result_(self);
    switch (value->Js.Json.decodeString) {
    | Some(str) => Some(`String(str))
    | None =>
      switch (value->asArrayBuffer) {
      | Some(ab) => Some(`ArrayBuffer(ab))
      | None => None
      }
    };
  };

[@bs.set] external onload: (t, Dom.event => unit) => unit = "onload";
[@bs.set] external onerror: (t, Dom.event => unit) => unit = "onerror";
[@bs.set] external onabort: (t, Dom.event => unit) => unit = "onabort";

[@bs.send] external abort: t => unit = "abort";

[@bs.new] external make: unit => t = "FileReader";

[@bs.send]
external readAsArrayBuffer: (t, FileReader_Blob.t) => unit =
  "readAsArrayBuffer";

/* readAsBinaryString is deprecated */

[@bs.send]
external readAsDataURL: (t, FileReader_Blob.t) => unit = "readAsDataURL";

[@bs.send] external readAsText: (t, FileReader_Blob.t) => unit = "readAsText";

[@bs.send]
external readAsText2: (t, FileReader_Blob.t, ~encoding: string) => unit =
  "readAsText";

exception FileReadError;

let toArrayBuffer = blob =>
  Js.Promise.make((~resolve, ~reject) => {
    let fr = make();
    fr->onload(_ =>
      switch (fr->result) {
      | Some(`ArrayBuffer(ab)) => resolve(. ab)
      | _ => reject(. FileReadError)
      }
    );
    fr->onerror(_ => reject(. FileReadError));
    fr->readAsArrayBuffer(blob);
  });

let toDataURL = blob =>
  Js.Promise.make((~resolve, ~reject) => {
    let fr = make();
    fr->onload(_ =>
      switch (fr->result) {
      | Some(`String(str)) => resolve(. str)
      | _ => reject(. FileReadError)
      }
    );
    fr->onerror(_ => reject(. FileReadError));
    fr->readAsDataURL(blob);
  });

let toText = blob =>
  Js.Promise.make((~resolve, ~reject) => {
    let fr = make();
    fr->onload(_ =>
      switch (fr->result) {
      | Some(`String(str)) => resolve(. str)
      | _ => reject(. FileReadError)
      }
    );
    fr->onerror(_ => reject(. FileReadError));
    fr->readAsText(blob);
  });

let toText2 = (blob, ~encoding: string) =>
  Js.Promise.make((~resolve, ~reject) => {
    let fr = make();
    fr->onload(_ =>
      switch (fr->result) {
      | Some(`String(str)) => resolve(. str)
      | _ => reject(. FileReadError)
      }
    );
    fr->onerror(_ => reject(. FileReadError));
    fr->readAsText2(blob, ~encoding);
  });

module File = FileReader_File;
module Blob = FileReader_Blob;
module BlobPart = FileReader_BlobPart;