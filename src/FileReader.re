type event;
type dom_exception;

type blob;
type file;
type t;

/*[@bs.new] [@bs.scope "self"]external make: unit => t = "FileReader";*/

/* wrap constructor to avoid name clashes */
/* @bs-scope' constructor as self/window can cause name clashes in user code */
/* 'unit' param is important */
let make: unit => t = [%raw {|
    function(unit) {
        return new FileReader();
    }
|}];

[@bs.get] external error_: t => Js.Nullable.t(dom_exception) = "error";
let error = self => error_(self)->Js.Nullable.toOption;

[@bs.get] external result_: t => Js.Json.t = "result";

let isArrayBuffer_: Js.Json.t => bool = [%raw
  {|
    function(value) {
        return value instanceof ArrayBuffer;
    }
|}
];

external asArrayBuffer__: Js.Json.t => Js.Typed_array.ArrayBuffer.t = "%identity";

let result: t => option([ | `String(string) | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)]) =
  self => {
    let value = result_(self);
    switch (value->Js.Json.decodeString) {
    | Some(str) => Some(`String(str))
    | None =>
      if (value->isArrayBuffer_) {
        Some(`ArrayBuffer(asArrayBuffer__(value)));
      } else {
        switch (value->Js.Json.decodeNull) {
        | Some(_) => None
        | None => failwith("unexpected result type")
        };
      }
    };
  };

[@bs.set] external onload: (t, event => unit) => unit = "onload";
[@bs.set] external onerror: (t, event => unit) => unit = "onerror";
[@bs.set] external onabort: (t, event => unit) => unit = "onabort";

[@bs.send] external abort: t => unit = "abort";

[@bs.send] external readAsArrayBuffer: (t, blob) => unit = "readAsArrayBuffer";
/* deprecated */
/*[@bs.send] external readAsBinaryString: (t, Blob.t) => unit = "readAsBinaryString";*/
[@bs.send] external readAsDataURL: (t, blob) => unit = "readAsDataURL";
[@bs.send] external readAsText: (t, blob, ~encoding: string=?, unit) => unit = "readAsText";

exception FileReadError;

module type TypeImpl = {type t;};

module Blob_ = (M: TypeImpl) => {
  [@bs.get] external size: M.t => float = "size";
  [@bs.get] external type_: M.t => string = "type";
};

module Blob = {
  type t = blob;

  include Blob_({
    type t = blob;
  });

  /* slice */

  /* self to avoid name clash with module iеself */
  [@bs.new] external makeUnsafe: (array('a), ~options: 'o=?, unit) => t = "Blob";

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

  let toText = (blob, ~encoding: option(string)=?, ()) =>
    Js.Promise.make((~resolve, ~reject) => {
      let fr = make();
      fr->onload(_ =>
        switch (fr->result) {
        | Some(`String(str)) => resolve(. str)
        | _ => reject(. FileReadError)
        }
      );
      fr->onerror(_ => reject(. FileReadError));
      fr->readAsText(blob, ~encoding?, ());
    });
};

module File = {
  type t = file;
  include Blob_({
    type t = file;
  });

  [@bs.get] external name: t => string = "name";
  [@bs.get] external lastModified: t => float = "lastModified";

  external asBlob: t => Blob.t = "%identity";

  /* self to avoid name clash with module iеself */
  [@bs.new] external makeUnsafe: (~bits: array('a), ~name: string, ~options: 'o=?, unit) => t = "File";
};
