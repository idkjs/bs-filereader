type t;

let error: t => option(Js.Json.t);
let result:
  t =>
  option([ | `String(string) | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)]);

let onload: (t, Dom.event => unit) => unit;
let onerror: (t, Dom.event => unit) => unit;
let onabort: (t, Dom.event => unit) => unit;

let abort: t => unit;

let make: unit => t;

let readAsArrayBuffer: (t, FileReader_Blob.t) => unit;
/* readAsBinaryString is deprecated */
let readAsDataURL: (t, FileReader_Blob.t) => unit;
let readAsText: (t, FileReader_Blob.t, ~encoding: string=?, unit) => unit;

exception FileReadError;

module File = FileReader_File;
module Blob = FileReader_Blob;
module BlobPart = FileReader_BlobPart;

let toArrayBuffer: Blob.t => Js.Promise.t(Js.Typed_array.ArrayBuffer.t);

let toDataURL: Blob.t => Js.Promise.t(string);

let toText: (Blob.t, ~encoding: string=?, unit) => Js.Promise.t(string);