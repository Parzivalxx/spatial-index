import { Dispatch, SetStateAction } from 'react';

export const handleMouseDown = (
  e: MouseEvent,
  setSelectionRect: Dispatch<SetStateAction<{ startX: number; startY: number; endX: number; endY: number }>>,
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
  setSelectionRect: Dispatch<SetStateAction<{ startX: number; startY: number; endX: number; endY: number }>>,
  xScale: d3.ScaleLinear<number, number>,
  yScale: d3.ScaleLinear<number, number>,
) => {
  const svgElement = e.currentTarget as SVGSVGElement;
  const svgRect = svgElement.getBoundingClientRect();

  // Calculate the adjusted mouse coordinates
  const x = xScale.invert(e.clientX - svgRect.left);
  const y = yScale.invert(e.clientY - svgRect.top);

  setSelectionRect((prevRect) => ({
    startX: Math.min(prevRect.startX, x),
    startY: Math.min(prevRect.startY, y),
    endX: Math.max(prevRect.startX, x),
    endY: Math.max(prevRect.startY, y),
  }));
};

export const handleMouseClick = (
  e: MouseEvent,
  setClickedX: Dispatch<SetStateAction<number>>,
  setClickedY: Dispatch<SetStateAction<number>>,
  xScale: d3.ScaleLinear<number, number>,
  yScale: d3.ScaleLinear<number, number>,
) => {
  const svgElement = e.currentTarget as SVGSVGElement;
  const svgRect = svgElement.getBoundingClientRect();

  const x = xScale.invert(e.clientX - svgRect.left);
  const y = yScale.invert(e.clientY - svgRect.top);

  setClickedX(x);
  setClickedY(y);
};
