export const handleMouseDown = (
  e: MouseEvent,
  setSelectionRect: React.Dispatch<
    React.SetStateAction<{ startX: number; startY: number; endX: number; endY: number }>
  >,
  xScale: d3.ScaleLinear<number, number>,
  yScale: d3.ScaleLinear<number, number>,
) => {
  // Start selecting when the mouse button is pressed
  const svgElement = e.currentTarget as SVGSVGElement;
  const svgRect = svgElement.getBoundingClientRect();

  // Calculate the adjusted mouse coordinates
  const x = xScale.invert(e.clientX - svgRect.left);
  const y = yScale.invert(e.clientY - svgRect.top);

  setSelectionRect({ startX: x, startY: y, endX: x, endY: y });
};

export const handleMouseUp = (
  e: MouseEvent,
  setSelectionRect: React.Dispatch<
    React.SetStateAction<{ startX: number; startY: number; endX: number; endY: number }>
  >,
  xScale: d3.ScaleLinear<number, number>,
  yScale: d3.ScaleLinear<number, number>,
) => {
  const svgElement = e.currentTarget as SVGSVGElement;
  const svgRect = svgElement.getBoundingClientRect();

  // Calculate the adjusted mouse coordinates
  const x = xScale.invert(e.clientX - svgRect.left);
  const y = yScale.invert(e.clientY - svgRect.top);
  console.log(x, y);

  setSelectionRect((prevRect) => ({
    startX: Math.min(prevRect.startX, x),
    startY: Math.min(prevRect.startY, y),
    endX: Math.max(prevRect.startX, x),
    endY: Math.max(prevRect.startY, y),
  }));
};
