using Blueprint.Blue;
using FlatSharp.Internal;
using System.Text;

namespace AVXFramework
{
    public class AVEngine
    {
        private Blueprint.Blue.Blueprint BlueprintLib;
        private Pinshot.Blue.PinshotLib PinshotLib;
        private const string SDK = "C:/src/AVX/omega/AVX-Omega-3911.data";
        private static readonly byte[] SDK_utf8 = Encoding.UTF8.GetBytes(SDK);
        private NativeText? Runtime;

        public AVEngine()
        {
            this.BlueprintLib = new();
            this.PinshotLib = new();

            this.Runtime = new NativeText(SDK_utf8);
        }
        public void Free()
        {
            if (this.Runtime != null)
                this.Runtime.Free();
            this.Runtime = null;
        }
        ~AVEngine()
        {
            this.Free();
        }
        public (QStatement? stmt, UInt64 cursor, string error, string result) Execute(string command)
        {
            var pinshot = this.PinshotLib.Parse(command);
            if (pinshot.root != null)
            {
                if (string.IsNullOrWhiteSpace(pinshot.root.error))
                {
                    var blueprint = this.BlueprintLib.Create(pinshot.root);

                    if (blueprint != null)
                    {
                        if (blueprint.IsValid)
                        {
                            if (blueprint.Singleton != null)
                            {
                                ; // process singleton command
                                return (blueprint, 0, "", "Pretend that this is the result of an executed Quelle command");
                            }
                            else if (blueprint.Commands != null)
                            {
                                UInt64 cursor = NativeLibrary.create_statement(QStatement.Serialize(blueprint.Blueprint));
                                var result = NativeLibrary.exec_statement(cursor);
                                var status = NativeLibrary.free_statement(cursor);

                                return (blueprint, cursor, "", "");
                            }
                            else
                            {
                                return (blueprint, 0, "Internal Error: Unexpected blueprint encountered.", "");
                            }
                        }
                        else
                        {
                            if (blueprint.Errors.Count > 0)
                            {
                                var errors = string.Join("; ", blueprint.Errors);
                                return (blueprint, 0, errors, "");
                            }
                            else
                            {
                                return (blueprint, 0, "Blueprint was invalid, but the error list was empty.", "");
                            }
                        }
                    }
                    else
                    {
                        return (blueprint, 0, "Blueprint was invalid (unexpected error).", "");
                    }
                }
                else
                {
                    return (null, 0, pinshot.root.error, "");
                }
            }
            return (null, 0, "Unable to parse the statement.", "");
        }
    }
}