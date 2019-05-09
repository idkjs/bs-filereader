type t = FileReader__.file;

include (module type of
  FileReader_BlobLike.Make({
    type nonrec t = t;
  }));

[@bs.get] external name: t => string = "name";
[@bs.get] external lastModified: t => float = "lastModified";

external asBlob: t => FileReader_Blob.t = "%identity";

module Options: {
  type t;

  [@bs.obj]
  external make: (~_type: string=?, ~lastModified: float=?, unit) => t = "";
};

let make: (array(FileReader_BlobPart.t), string) => t;

let makeWithOptions: (array(FileReader_BlobPart.t), string, Options.t) => t;