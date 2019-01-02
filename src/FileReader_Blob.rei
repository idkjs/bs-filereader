type t = FileReader_Types.blob;

include (module type of
  FileReader_BlobLike.Make({
    type nonrec t = t;
  }));

let make:
  (
    array(FileReader_BlobPart.t),
    ~type_: string=?,
    ~endings: string=?,
    unit
  ) =>
  t;