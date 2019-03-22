type t = FileReader__.blob;

include (module type of
  FileReader_BlobLike.Make({
    type nonrec t = t;
  }));

let asFile: t => option(FileReader__.file);

let make:
  (
    array(FileReader__.blobPart),
    ~type_: string=?,
    ~endings: string=?,
    unit
  ) =>
  t;
