type t = FileReader_Types.file;

include FileReader_BlobLike.Make({
  type nonrec t = t;
});

[@bs.get] external name: t => string = "name";
[@bs.get] external lastModified: t => float = "lastModified";

external asBlob: t => FileReader_Blob.t = "%identity";

module Options = {
  type t;

  [@bs.obj]
  external make: (~_type: string=?, ~lastModified: float=?, unit) => t = "";
};

[@bs.new] external make: (array(FileReader_BlobPart.t), string) => t = "File";

[@bs.new]
external make3: (array(FileReader_BlobPart.t), string, Options.t) => t =
  "File";