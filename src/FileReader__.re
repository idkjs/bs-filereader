type blob;
type file;

type blobPart = [
  | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)
  | `Int8Array(Js.Typed_array.Int8Array.t)
  | `Uint8Array(Js.Typed_array.Uint8Array.t)
  | `Uint8ClampedArray(Js.Typed_array.Uint8ClampedArray.t)
  | `Int16Array(Js.Typed_array.Int16Array.t)
  | `Uint16Array(Js.Typed_array.Uint16Array.t)
  | `Int32Array(Js.Typed_array.Int32Array.t)
  | `Uint32Array(Js.Typed_array.Uint32Array.t)
  | `Float32Array(Js.Typed_array.Float32Array.t)
  | `Float64Array(Js.Typed_array.Float64Array.t)
  | `DataView(Js.Typed_array.DataView.t)
  | `Blob(blob)
  | `String(string)
];

external anyToJsonUnsafe: 'a => Js.Json.t = "%identity";

let blobPartToJson =
  fun
  | `ArrayBuffer(x) => anyToJsonUnsafe(x)
  | `Int8Array(x) => anyToJsonUnsafe(x)
  | `Uint8Array(x) => anyToJsonUnsafe(x)
  | `Uint8ClampedArray(x) => anyToJsonUnsafe(x)
  | `Int16Array(x) => anyToJsonUnsafe(x)
  | `Uint16Array(x) => anyToJsonUnsafe(x)
  | `Int32Array(x) => anyToJsonUnsafe(x)
  | `Uint32Array(x) => anyToJsonUnsafe(x)
  | `Float32Array(x) => anyToJsonUnsafe(x)
  | `Float64Array(x) => anyToJsonUnsafe(x)
  | `DataView(x) => anyToJsonUnsafe(x)
  | `Blob(x) => anyToJsonUnsafe(x)
  | `String(x) => anyToJsonUnsafe(x);
